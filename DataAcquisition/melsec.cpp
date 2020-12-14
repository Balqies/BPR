#include "melsec.h"
Melsec::Melsec(){

}

bool Melsec::init(){
#ifdef LINUX

    //Table structure for data logging.
    TableStructure tableDataStructure;

    //Table structure for data items.

    // 1. add placeholder for memory address
    TableStructure tableItemStructure = PluginInterface::createTableStructure("memory_address", DatabaseColumnStructure::TEXT, 0);

    // 2. add placeholder for data type
    DatabaseColumnStructure dataTypeStructure ("data_type", DatabaseColumnStructure::INT, 3);
    for (int type = 0; type < DataTypes::UNKNOWN; type++) {
        dataTypeStructure.insertSelectionValues(this->formater.dataTypesToString(DataTypes(type)),QString::number(DataTypes(type)));
    }
    tableItemStructure.push_back(dataTypeStructure);
    //Table structure for device logging.
    //Device: Frame type, IP, port, device Id, network id
    TableStructure tableDeviceStructure;
    //select type of frame that the device can use to communicate in MC protocol
    DatabaseColumnStructure frameTypeStructure("frame_type",DatabaseColumnStructure::TEXT, 3);
    frameTypeStructure.insertSelectionValues("1E_Ascii" , QString::number(ASCII_1E));
    frameTypeStructure.insertSelectionValues("1E_Binary", QString::number(BINARY_1E));
    frameTypeStructure.insertSelectionValues("3E_Ascii" , QString::number(ASCII_3E ));
    frameTypeStructure.insertSelectionValues("3E_Binary", QString::number(BINARY_3E));
    frameTypeStructure.insertSelectionValues("4E_Ascii" , QString::number(ASCII_4E ));
    frameTypeStructure.insertSelectionValues("4E_Binary", QString::number(BINARY_4E));
    tableDeviceStructure.push_back(frameTypeStructure);
    DatabaseColumnStructure deviceIdStructure("device_id", DatabaseColumnStructure::TEXT,3);
    tableDeviceStructure.push_back(deviceIdStructure);
    DatabaseColumnStructure networkIdStructure("network_id", DatabaseColumnStructure::TEXT,3);
    tableDeviceStructure.push_back(networkIdStructure);
    DatabaseColumnStructure tcpPortStructure("port",DatabaseColumnStructure::INT, 3);
    tcpPortStructure.insertSelectionValues("default" , QString::number(5500));
    tableDeviceStructure.push_back(tcpPortStructure);
#ifndef APP
    interface.initPlugin(NAME, 12, tableDataStructure, tableItemStructure, tableDeviceStructure, {}, false, false);
#endif

#endif
    return  false;
}

bool Melsec::readData(LogList *data){
    DeviceInstancePlugin *device =&data->device; // shortcut for device
    if (!this->hasConnection(device)) {
        connectDevice(device);
    }

    if (this->hasConnection(device))
    {

        int err;
        for (int i = 0; i < data->list.length(); ++i) {
            err = makeFrame(READ, data->device,  data->list[i], &sendBuffer);
            if(err)
            {
                qWarning()<<checkData.errorToString(err);
                continue;
            }
            bool sent = getDeviceConnection(device).write(sendBuffer); // send request to PLC
            if (!sent) {
                continue;
            }

            bool received = getDeviceConnection(device).read(&replyBuffer, 600); // read data frrom PLC
            if (!received) {
                //this->connected = false;
                continue;
            }
            err = frame.decodeResponse(data->device.userDefinedFields["frame_type"].toInt(), sendBuffer,replyBuffer,&dataFromPLC);
            if(err)
            {
                qWarning()<<checkData.errorToString(err);
                continue;
            }
            else
            {
                if (DataTypes (data->list[i].item.userDefinedFields["data_type"].toInt())== DataTypes::BOOL)
                {
                    dataFromPLC = formater.bitFromPLCtoItem (dataFromPLC, QString::number(checkData.bitNo)).toUtf8();
                    qWarning() << dataFromPLC <<"data";
                }
                else
                {
                    dataFromPLC = formater.fromHextoAscii(DataTypes (data->list[i].item.userDefinedFields["data_type"].toInt()),dataFromPLC); //format the data from PLC (hex) to user requested format
                }
                data->list[i].values["value"] = dataFromPLC;
            }

        }
    }else {
        return false;
    }
    return  true;
}

bool Melsec::writeData(LogList *data){
    DeviceInstancePlugin *device =&data->device;
    if (!this->hasConnection(device)) {
        connectDevice(device);
    }
    if (this->hasConnection(device)) {
        QByteArray reply;
        int err ;
        for (int i = 0; i < data->list.length(); ++i) {

            if (!data->list[i].item.userDefinedFields["data_type"].toInt()) // if data type  BOOL
            {
                err = makeFrame(READ, data->device,  data->list[i], &sendBuffer);                       // make  frame to check validity of arguments
                if(err)
                {
                    qWarning()<<checkData.errorToString(err);
                    continue;
                }
                auto memDev = checkData.memoryAddress;                                                  // save memory address
                auto bitValue =  data->list[i].values["value"] ;                                        //save bit value
                auto bitNo = checkData.bitNo;                                                           // save bit number
                data->list[i].item.userDefinedFields["data_type"] = QString::number(DataTypes::UINT16);  // force data type to int 16
                data->list[i].item.userDefinedFields["memory_address"]=checkData.memoryAddress;         //force the non-dot notation for device
                err = makeFrame(READ, data->device,  data->list[i], &sendBuffer);                       // make  frame to read data from PLC
                qWarning() << "1";
                if(err)
                {
                    qWarning()<<checkData.errorToString(err);
                    continue;
                }
                getDeviceConnection(device).write(sendBuffer); // get data from PLC
                getDeviceConnection(device).read(&replyBuffer, 500);
                int err = frame.decodeResponse(data->device.userDefinedFields["frame_type"].toInt(), sendBuffer,replyBuffer,&dataFromPLC); //decode data from PLC

                if(err)
                {
                    qWarning()<<checkData.errorToString(err);
                    continue;
                }

                auto intFromPLC = dataFromPLC.toInt(nullptr,16);

                qWarning () <<" data: " << dataFromPLC;

                bitValue.toUInt()?  BIT_SET(intFromPLC,bitNo): BIT_CLEAR(intFromPLC,bitNo); // make number from set/clear bit at bitNo and int from PLC
                data->list[i].values["value"] = QString::number(intFromPLC); // force item data as new number
                err = makeFrame( WRITE, data->device,  data->list[i], &sendBuffer); // make frame for writing new number
                qWarning() << "2";
                if(err)
                {
                    qWarning()<<checkData.errorToString(err);
                    continue;
                }

                getDeviceConnection(device).write(sendBuffer); // get data from PLC
                getDeviceConnection(device).read(&replyBuffer, 500);
                err = frame.decodeResponse(data->device.userDefinedFields["frame_type"].toInt(), sendBuffer,replyBuffer,&dataFromPLC);
                if(err)
                {
                    qWarning()<<checkData.errorToString(err);
                    continue;
                }

                data->device.userDefinedFields["memory_address"]=checkData.memoryAddress; // restore device memory address
                data->list[i].values["value"] = bitValue; //restore item data
                data->list[i].item.userDefinedFields["data_type"] = QString::number(DataTypes::BOOL); // restore data type to bool
                continue; //skip the rest of the loop iteration as job for if BOOL is done
            }

            // end of if(BOOL)
            err = makeFrame( WRITE, data->device,  data->list[i], &sendBuffer);
            if(err)
            {
                qWarning()<<checkData.errorToString(err);
                continue;
            }

            getDeviceConnection(device).write(sendBuffer); // get data from PLC
            getDeviceConnection(device).read(&replyBuffer, 500);
            int err = frame.decodeResponse(data->device.userDefinedFields["frame_type"].toInt(), sendBuffer,replyBuffer,&dataFromPLC);
            if(err)
            {
                qWarning()<<checkData.errorToString(err);
                continue;
            }

        }
        return true;
    }else {

        return false;
    }


    return  true;
}

bool Melsec:: getEventData(LogList *data){
    *data = *data;
    return  false;
}
bool Melsec::logCallback(LogList *data){
    *data = *data;
    return  false;
}
bool Melsec::stopPlugin(){
    foreach (Socket s, sockets) {
        s.disconnect();
    }
    return  false;
}

int Melsec::makeFrame(int command, DeviceInstancePlugin device, DataItem dataItem, QByteArray *sendBuff){
    uint16_t frameType = device.userDefinedFields["frame_type"].toUShort();
    QString network_id = device.userDefinedFields["network_id"];
    QString device_id = device.userDefinedFields["device_id"];
    int err = checkData.validate( command, dataItem.item.userDefinedFields["memory_address"],dataItem.values["value"].toUtf8(),dataItem.item.userDefinedFields["data_type"]);
    if (err)
    {
        return err;
    }
    QByteArray data;
    QString zeroStart = "00";
    auto destination = QString(zeroStart.right(zeroStart.length()-network_id.length()) + network_id)+
            QString(zeroStart.right(zeroStart.length()-device_id.length()) + device_id) ;
    QByteArray timeout = dataItem.item.userDefinedFields["timeout_read_ms"].toUtf8();
    QByteArray memArea = checkData.device.toUtf8();
    QByteArray startPoint = checkData.deviceHeadNo.toUtf8();
    command ?  data = formater.fromAsciiToHex(DataTypes(dataItem.item.userDefinedFields["data_type"].toInt()),checkData.data).toUpper().toUtf8() : data = "";
    QByteArray noOfpoints = formater.getSizeInWords(DataTypes(dataItem.item.userDefinedFields["data_type"].toInt()));
    *sendBuff = frame.make(destination, timeout, command, memArea, startPoint, noOfpoints, data, frameType );
    return  0;
}

QByteArray Melsec::makeBinaryFrame(QByteArray frame){
    return formater.fromHextoAscii(ASCII,frame);
}
int Melsec::connectDevice(DeviceInstancePlugin *device){

    if (!makeSocket(device)) {
        this->connections.insert(device->id,device->address);
    }
    return 0;
}

bool Melsec::makeSocket(DeviceInstancePlugin *device)
{
    bool socketMade;
    foreach (Socket socket, sockets) {
        socketMade = socket.hasIpAndPort(device->address, device->userDefinedFields["port"].toInt());
        if (socketMade) {
            return socketMade;
        }
    }

    sockets.append(Socket(device->address,  device->userDefinedFields["port"].toUInt(), 500)); // replace static value 500 with user timeout
    return socketMade;
}

Socket Melsec::getDeviceConnection(DeviceInstancePlugin *device)
{
    bool deviceConnected;
    foreach (Socket socket, sockets) {
        deviceConnected = socket.hasIpAndPort(device->address, device->userDefinedFields["port"].toInt());
        if (deviceConnected) {
            return socket;
        }
    }
    return Socket();
}

bool Melsec::hasConnection(DeviceInstancePlugin *device){

    return this->connections.contains(device->id);
}
