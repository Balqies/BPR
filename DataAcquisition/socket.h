#ifndef SOCKET_H
#define SOCKET_H


#include <QString>
#include <QDebug>
#include <QThread>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <algorithm>
#include <string>
#include <vector>
#include <fcntl.h>
#include <signal.h>

class  Socket
{

private:
    int sockfd;
    int port;
    QString ip;
public:
    Socket()= default;
    Socket(QString TcpIp, int port, int timeoutMilliSeconds);
    bool connect(QString TcpIp, int port, int *sockfd, int timeoutMilliSeconds);
    int disconnect();
    bool read( QByteArray *data, int timeoutMilliSeconds);
    bool write(QByteArray data);
    bool write(const void *data, int length);
    QString getIp();
    int getPort();
    bool hasIpAndPort(QString ip, int port);
    ~Socket();
};

#endif // SOCKET_H
