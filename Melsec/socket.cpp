#include "socket.h"
#define logError(str)  qWarning() << str

Socket::Socket(QString tcpIp, int port, int timeoutMilliSeconds)
{
    connect(tcpIp,port, &sockfd, timeoutMilliSeconds);
    this->ip = tcpIp;
    this->port= port;
    logError(timeoutMilliSeconds);
}
Socket::~Socket(){
    //disconnect();
}


bool Socket::connect(QString TcpIp, int port, int *sockfd, int timeoutMilliSeconds) {

    //Connect
    int res;
    struct timeval tv;
    fd_set myset;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == (void *) NULL) {
        close(*sockfd);
        logError("Error opening socket");
        return false;
    }
    server = gethostbyname(TcpIp.toStdString().c_str());
    if (server == NULL) {
        close(*sockfd);
        logError("Eror resolving host: "+ TcpIp);
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);

    //Avoid SIGPIPE if not connected and trying to write
    signal(SIGPIPE, SIG_IGN);

    // Set non-blocking
    long arg = 0;
    if( (arg = fcntl(*sockfd, F_GETFL, NULL)) < 0) {
        logError("Error fcntl F_GETFL "+ QString(strerror(errno)));
        close(*sockfd);
        return false;
    }
    arg |= O_NONBLOCK;
    if( fcntl(*sockfd, F_SETFL, arg) < 0) {
        logError("Error fcntl F_SETFL "+ QString(strerror(errno)));
        close(*sockfd);
        return false;
    }

    res = ::connect(*sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if (res < 0) {
        if (errno == EINPROGRESS || errno == EAGAIN || errno == EWOULDBLOCK) {
            tv.tv_sec = 0;
            tv.tv_usec = timeoutMilliSeconds * 1000;
            FD_ZERO(&myset);
            FD_SET(*sockfd, &myset);
            res = select(*sockfd+1, NULL, &myset, NULL, &tv);
            if (res < 0 && errno != EINTR) {
                this->disconnect();
                logError("Error connecting to Tcp module (select): "+ TcpIp +" Error: "+ QString(strerror(errno)));
                return false;
            } else if (res > 0) {
                logError("Connected to: " + TcpIp);
            } else {
                this->disconnect();
                logError("Timeout connecting to Tcp module: "+ TcpIp +" Timeout: "+ QString::number(timeoutMilliSeconds) +"s");
                return false;
            }
        } else {
            this->disconnect();
            logError("Error connecting to Tcp module: "+ TcpIp +" Error: "+ QString(strerror(errno)));
            return false;
        }
    }


    if( (arg = fcntl(*sockfd, F_GETFL, NULL)) < 0) {
        logError("Error fcntl F_GETFL "+ QString(strerror(errno)));
        return false;
    }
    arg &= (~O_NONBLOCK);
    if( fcntl(*sockfd, F_SETFL, arg) < 0) {
        logError("Error fcntl F_SETFL "+ QString(strerror(errno)));
        return false;
    }
    logError("Connecting to Tcp module: "+ TcpIp +" Error: "+ QString(strerror(errno)));

    return true;
}
int Socket::disconnect() {
    logError("Disconnect from Tcp module. Socket no.:"+ QString::number(this->sockfd) );
    close(this->sockfd);
    return 0;

}

bool Socket::read( QByteArray *data, int timeoutMilliSeconds) {
    fd_set set;
    struct timeval timeout;
    int rv;
    uint16_t bufferSize = std::numeric_limits<uint32_t>::max();
    char buffer[bufferSize];
    bzero(buffer, bufferSize);
    data->clear();
    timeout.tv_sec = 0;
    timeout.tv_usec = timeoutMilliSeconds * 1000;
    FD_ZERO(&set); // clear the set
    FD_SET(this->sockfd, &set); // add our file descriptor to the set
    rv = select(this->sockfd + 1, &set, NULL, NULL, &timeout);
    if(rv == -1) {
        logError("Error reading from Tcp module (select): Error: "+ QString(strerror(errno)) +" ("+ QString::number(rv) +")");
        this->disconnect();
        return false;
    } else if(rv == 0) {
        logError("Timeout reading from Tcp module ("+ QString::number(timeoutMilliSeconds)+"ms)");
        this->disconnect();
        return false;
    }

    int n = ::read(this->sockfd, buffer, sizeof buffer/*bufferSize*/);
    if (n <= 0) {
        //this->disconnect(sockfd);
        logError("No data received - "+ QString(strerror(errno)) +" Read bytes: "+ QString::number(n) +" FD: "+ QString::number(this->sockfd));
        return false;
    }

    *data = QByteArray::fromRawData(buffer, n);
    logError("read :" + *data);
    return true;
}
bool Socket::write(QByteArray data) {
    logError("try write :" + data+ " " +QString(sockfd));
    int n = send(sockfd, data, data.length(), MSG_NOSIGNAL);
    if (n < 0) {
        logError("Tcp error writing: "+ QString(strerror(errno))+QString(n));
        this->disconnect();
        return false;
    }
    logError("written :" + data/*+ " " +QString(n)*/);
    return true;
}

bool Socket::write(const void* data, int length) {
    int n = send(this->sockfd, data, length, MSG_NOSIGNAL); //Avoid NOSIGPIPE signal if not a valid endpoint to write to
    if (n < 0) {
        logError("Tcp error writing: "+ QString(strerror(errno)));
        this->disconnect();
        return false;
    }

    return true;
}

QString Socket::getIp()
{
    return this->ip;
}

int Socket::getPort()
{
    return  this->port;
}

bool Socket::hasIpAndPort(QString ip, int port)
{
    return  ((getPort()==port)&&(getIp()==ip));
}





/* to test
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Socket s;
    int sockfd;
    s.connect("10.20.30.115", 5500, &sockfd, 500);
    QByteArray garbage = "db8854b8";
    QByteArray reset_err = "5000010103FF00000C000216170000";

    s.write(&sockfd, reset_err);
    s.read(&sockfd, &reset_err,500);
    s.disconnect(&sockfd);
    logError("here");
    return 0;
}

*/
