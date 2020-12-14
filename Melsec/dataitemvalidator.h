#ifndef DATAITEMVALIDATOR_H
#define DATAITEMVALIDATOR_H
#include "memorydevice.h" //for the list of devices specific to this dataItems
#include "dataformater.h" //for the list of datatypes specific to this dataItems
#define test_bit(bitNo, data, df) (df.bitFromItemtoPLC(data,bitNo,df.bitFromPLCtoItem(data,bitNo).toUtf8())==data)
#define test(type, data, df) (df.fromHextoAscii(type,df.fromAsciiToHex(type,data).toUtf8())==data)

// here is

class DataItemValidator
{
public:
    /*!
     * \brief DataItemValidator 
     */
    DataItemValidator();
    enum Error{
        //from system
        no_error,
        dataType_not_boolean,
        invalid_address,
        data_lenght_invalid,
        invalid_data_provided,
        no_data_provided,
        //from PLC
        protocol_error,
        subheader_command, // 50H
        ascii_code_not_enabled, //54H
        device_designation, //56H
        number_of_points, //57H
        head_device_number, //58H
        PLC_id, //5BH - 10H
        ethernet_communication, //5BH - 11H
        remote_error, //5BH - 18H
        monitor_time_overflow, //60H
        unknown_error

    };
    
    /*!
     * \brief validate: performs a check if data value parsed is compatible with the data type, the memery address and the lenght of the data
     * \param command integer 0-read/1-write
     * \param memoryAddress PLC memory area 
     * \param data value as string
     * \param dataType type of value in data string
     * \param dataLenght size of data in words  
     * \return  mismatch error codes 
     */
    int validate(int command, QString memoryAddress, QString data, QString dataType);
    QByteArray errorToString(int err);
    ushort bitNo ;
    QString device;
    QString deviceHeadNo;
    QString data;
    QString memoryAddress;
    MemoryDevice memoryDevice;
    DataFormater format;
};

#endif // DATAITEMVALIDATOR_H
