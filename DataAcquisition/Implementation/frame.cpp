#include "frame.h"
#include <QDebug>

Frame::Frame(){}

QByteArray Frame::make(QString destination, QByteArray monitorTimer, int genericCmd, QByteArray devCode, QByteArray devHeadNo,QByteArray devNoOfPoints, QByteArray data, int frameType)
{
    QByteArray frame;
    bool isBinary = false;

    switch (frameType) {
    case ASCII_1E:
        frame = (frameSpecificCmd(genericCmd, devCode, frameType) +
                 destination.toUtf8() +
                 mcMonitorTimer(monitorTimer) +
                 e1DevCode(devCode) +
                 mcHeadNo(devHeadNo) +
                 mcDataLenght(devNoOfPoints) +
                 fixedVAlFor1E +
                 data);
        break;

    case BINARY_1E:
        frame = (toBinary(frameSpecificCmd(genericCmd, devCode, frameType)) +
                 toBinary(destination.toUtf8()) +
                 toBinary(mcMonitorTimer(monitorTimer)) +
                 toBinary(mcHeadNo(devHeadNo)) +
                 toBinary(e1DevCode(devCode)) +
                 toBinary(mcDataLenght(devNoOfPoints)) +
                 toBinary(fixedVAlFor1E) +
                 toBinary(data));
        break;

    case BINARY_3E:
        isBinary = true;
    case ASCII_3E:
        frame = (subheader3E(destination, isBinary)+message3E(monitorTimer, genericCmd ,frameType ,devCode, devHeadNo, devNoOfPoints, data, isBinary));
        break;
    case BINARY_4E:
        isBinary = true;
    case ASCII_4E:
        frame = (subheader4E(destination, false) + message3E(monitorTimer, genericCmd ,frameType ,devCode, devHeadNo, devNoOfPoints, data, false));
        break;

    }
    return  frame;
}


QByteArray Frame::frameSpecificCommand(int userCommand, QByteArray devCode){
    QString zeroStart = "00";
    QString hexinput=QString::number(userCommand + device.isWordDevice(devCode),16).toUpper();
    return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
}

QByteArray Frame::mcHeadNo(QByteArray headNo){
    QString zeroStart = "000000";
    headNo = QString::number(headNo.toInt(nullptr,10),16).toUpper().toUtf8();// number of head is to be  sent as hex
    return QString(zeroStart.right(zeroStart.length()-headNo.length()) +headNo).toUtf8();
}

QByteArray Frame::e3HeadNo(QByteArray headNo){
    QString zeroStart = "000000";
    headNo = QString::number(headNo.toInt(nullptr,10),10).toUpper().toUtf8();// number of head is to be  sent as hex
    return QString(zeroStart.right(zeroStart.length()-headNo.length()) +headNo).toUtf8();
}


QByteArray Frame:: e1DevCode(QByteArray userDevCode){
    return device.E1.value(userDevCode).toUtf8();
}

QByteArray Frame:: e3DevCode(QByteArray userDevCode){
    return device.E3.value(userDevCode).toUtf8();
}
QByteArray Frame:: e3bDevCode(QByteArray userDevCode){
    return device.E3B.value(userDevCode).toUtf8();
}

QByteArray Frame::mcMonitorTimer(QByteArray userMonitorTimer){
    QString zeroStart = "0000";
    QString hexinput=QString::number(userMonitorTimer.toInt(),16).toUpper();
    return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
}

QByteArray Frame::e1DestinationNo(int userDestination){
    QString zeroStart = "00";
    QString hexinput=QString::number(userDestination,16).toUpper();
    return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
}
QByteArray Frame::e3DestinationNo(int userDestination){
    QString zeroStart = "0000";
    QString hexinput=QString::number(userDestination,10).toUpper();
    return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
}

QByteArray Frame::mcDataLenght(QByteArray devNoOfPoints){
    QString zeroStart = "0000";
    QString hexinput=QString::number(devNoOfPoints.toUShort(),16).toUpper();
    return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
}

QByteArray Frame::toBinary(QByteArray chars){
    QByteArray binary;
    for (int i = 0; 1 < chars.length();i++) {
        binary.append(chars.right(2).toShort(nullptr,16));
        chars.remove(chars.length()-2,2);
    }
    return binary;
}

QByteArray Frame::toBinaryData(QByteArray chars){
    QByteArray binary;
    for (int i = 0; 1 < chars.length();i++) {
        binary.append(chars.left(2).toShort(nullptr,16));
        chars.remove(0,2);
    }
    return binary;
}
int Frame::decodeResponse(int  frameType, QByteArray frame, QByteArray response, QByteArray *data)
{
    switch (frameType)
    {
    case BINARY_1E:
    case ASCII_1E:
        return decode1EResponse(frameType, frame, response, data);
    case BINARY_3E:
    case BINARY_4E:
    case ASCII_3E:
    case ASCII_4E:
        return  decode3EResponse(frameType, response, data);
    }

    return  0;
}

int Frame::decode1EResponse(int  frameType, QByteArray frame, QByteArray response, QByteArray *data){

    // for the meaning and source of each value see tables frame.h:1 and frame.h:25
    if (frameType!= BINARY_1E)
        toBinary(frame);

    if (((response[0]|0x00)+0x80)!=(frame[0]|0x00) )
        return DataItemValidator::Error::protocol_error;

    if (((response[1]|0x00))==0x50)
        return DataItemValidator::Error::protocol_error;

    if (((response[1]|0x00))==0x54)
        return DataItemValidator::Error::protocol_error;

    if (((response[1]|0x00))==0x56)
        return DataItemValidator::Error::protocol_error;

    if (((response[1]|0x00))==0x57)
        return DataItemValidator::Error::protocol_error;

    if (((response[1]|0x00))==0x5B) {

        if (((response[2]|0x00))==0x10)
            return DataItemValidator::Error::PLC_id;

        if (((response[2]|0x00))==0x11)
            return DataItemValidator::Error::ethernet_communication;

        if (((response[2]|0x00))==0x18)
            return DataItemValidator::Error::remote_error;
    }
    if (((response[1]|0x00))==0x60)
        return DataItemValidator::Error::protocol_error;

    *data= response.remove(0,2);
    if (frameType == BINARY_1E)
    {
        *data = getAsciiResponseFromBinary(*data);
    }
    return DataItemValidator::Error::no_error;
}


int Frame::decode3EResponse(int  frameType, QByteArray response, QByteArray *data){

    if (frameType == ASCII_3E || frameType == ASCII_4E)
    {
        int err = response.left(22+(frameType==ASCII_4E ? 8 : 0)).right(4).toInt(nullptr,16);
        if (err)
        {
            return err;
        }

        int dataLenght = response.left(18 + (frameType==ASCII_4E ? 8 : 0)).right(4).toInt(nullptr, 16) - 4 ;// substract response code lenght since it is considered data eve if it is not
        *data = response.right(dataLenght);

    }
    if (frameType == BINARY_3E || frameType == BINARY_4E)
    {
        QByteArray tempResponse, invResponse;

        foreach (uint8_t byte, response) {
            tempResponse.append(QString::number(byte, 16).toUpper().toUtf8());
            invResponse.prepend(QString::number(byte, 16).toUpper().toUtf8());
        }
        response = tempResponse;
        int err = invResponse.right(13+(frameType==BINARY_4E ? 6 : 0)).left(2).toInt(nullptr,16);
        int dataLenght = (invResponse.right(11+(frameType==BINARY_4E ? 6 : 0)).left(2).toInt(nullptr,16)-2)*2;
        *data = getAsciiResponseFromBinary(toBinaryData(invResponse.left(dataLenght)));
        qWarning()<<"decoding binary frames"<<*data<<Frame::getAsciiResponseFromBinary(toBinaryData(*data));
    }
    return DataItemValidator::Error::no_error;
}

QByteArray Frame::getAsciiResponseFromBinary(QByteArray binaryResponse){
    QByteArray asciiRseponse;
    foreach (char ch, binaryResponse)
    {
        QByteArray strChar = QString::number(uint8_t(ch),16).toUpper().toUtf8();
        if (strChar.length()<2) strChar = "0"+strChar;
        asciiRseponse = strChar + asciiRseponse;
    }
    return asciiRseponse;
}

QByteArray Frame::frameSpecificCmd(int userCommand, QByteArray devCode, int frameType)
{

    if (frameType == ASCII_1E || frameType == BINARY_1E)
    {
        QString zeroStart = "00";
        QString hexinput=QString::number(userCommand*2 + device.isWordDevice(devCode),16).toUpper();
        return  QString(zeroStart.right(zeroStart.length()-hexinput.length()) + hexinput).toUtf8();
    }

    else if (frameType == ASCII_3E  || frameType == ASCII_4E)
    {
        return (QString::number(userCommand) + "40" + QString::number(1/*replace with is_multiple block()+1*/)+"0000").toUtf8();
    }
    else if (frameType == BINARY_3E  || frameType == BINARY_4E)
    {
        return ("0000" + QString::number(userCommand) + "40" + QString::number(1/*replace with is_multiple block()+1*/)).toUtf8();
    }
    else
    {

    }
    return "";
}

QByteArray Frame:: subheader3E(QString stationNo, bool isBinary )
{
    // note: for binary commands the position of deviceHeadNo and deviceCode is inverted with respect to the ascii command
    // note: data to be written does not follow the rule of inversion as the rest of the command components
    QByteArray subheader = (isBinary)?
                Frame::toBinaryData(Frame::subheader_3E.toUtf8())
                + Frame::toBinaryData(stationNo.toUtf8())
                + Frame::toBinary(Frame::def_RDM_IO.toUtf8())
                + Frame::toBinary(Frame::def_RDM_S.toUtf8())
              :
                Frame::subheader_3E.toUtf8() + stationNo.toUtf8() + Frame::def_RDM_IO.toUtf8() + Frame::def_RDM_S.toUtf8();
    return subheader;

}

QByteArray Frame:: subheader4E(QString stationNo ,bool isBinary)
{
    QByteArray subheader = (isBinary)?
                Frame::toBinaryData(Frame::subheader_4E.toUtf8())
                + Frame::toBinary(serialNo()) + toBinary(QString("0000").toUtf8())
                + Frame::toBinaryData(stationNo.toUtf8())
                + Frame::toBinary(Frame::def_RDM_IO.toUtf8())
                + Frame::toBinary(Frame::def_RDM_S.toUtf8())
              :
                Frame::subheader_4E.toUtf8() + serialNo() + "0000" + stationNo.toUtf8() + Frame::def_RDM_IO.toUtf8() + Frame::def_RDM_S.toUtf8();
    return subheader;
}

QByteArray Frame::serialNo()
{
    qsrand(uint(QDateTime::currentMSecsSinceEpoch()));
    QByteArray sn = QByteArray:: number(qrand() % 9999);
    while (sn.length() < 4) {
        sn.prepend("0");
    }
    return sn;
}

QByteArray Frame:: message3E( QByteArray monitorTimer, int genericCmd, int frameType, QByteArray devCode,QByteArray devHeadNo, QByteArray devNoOfPoints, QByteArray data, bool isBinary )
{
    QByteArray tempMessage = (isBinary) ?
                toBinary(mcMonitorTimer(monitorTimer)) +
                toBinary(frameSpecificCmd(genericCmd, devCode, frameType)) +
                toBinary(mcHeadNo(devHeadNo)) +
                toBinary(e3bDevCode(devCode)) +
                toBinary(mcDataLenght(devNoOfPoints)) +
                toBinary(data)
              :
                mcMonitorTimer(monitorTimer) +
                frameSpecificCmd(genericCmd, devCode,frameType) +
                e3DevCode(devCode) +
                e3HeadNo(devHeadNo) +
                mcDataLenght(devNoOfPoints) +
                data;
    QByteArray message = (isBinary) ?
                toBinary(mcDataLenght(QString::number(tempMessage.length()).toUtf8()))+tempMessage
              :
                mcDataLenght(QString::number(tempMessage.length()).toUtf8())+tempMessage;




    return message;
}

