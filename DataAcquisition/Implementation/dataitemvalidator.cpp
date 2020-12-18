#include "dataitemvalidator.h"

DataItemValidator::DataItemValidator()
{
}
int DataItemValidator::validate(int command, QString memoryAddress, QString value, QString dataType)
{

    this->memoryAddress = memoryAddress;
    DataTypes type = DataTypes(dataType.toUShort());
    this->bitNo = 0; //reset
    this->data=(command) ? value : "";
    QRegularExpression
            numbers("\\d+"),
            letters("(\\D)+"),
            withDot("^\\D+[0-9]+\\.[0-9]+$"),
            noDot("^\\D+[0-9]+$"),
            boolRegex("^[0-1]$"),
            uintRegEx("^[0-9]+$"),
            intRegEx("^[-+]?[0-9]+$"),
            floatRegEx("^[-+]?[0-9]*\\.?[0-9]+$"),
            hexRegEx("^[0-9a-fA-F]+$"),
            stringRegEx("^[\\D\\d]+$");
    if (withDot.match(memoryAddress).hasMatch())
    {
        this->memoryAddress = memoryAddress.split('.')[0];
        this->device = letters.match(memoryAddress.split('.')[0]).captured().toUpper(); //extract the area letter for later use
        this->deviceHeadNo = numbers.match(memoryAddress.split('.')[0]).captured();//extract the number of the (first) data word for later use
        this->bitNo= memoryAddress.split('.')[1].toUShort(); // extract the number after '.' to use it as bit number
        if (type != DataTypes::BOOL)
        {
            return Error::dataType_not_boolean;
        }
        if (!(value.toInt() == 0 || value.toInt() == 1))
        {
            qWarning() << "!!!"<< value.toInt();
            return Error::dataType_not_boolean;
        }
    }
    else if (noDot.match(memoryAddress).hasMatch())
    {
        this->device = letters.match(memoryAddress).captured().toUpper(); //extract the device letter for later use
        if (!memoryDevice.isWordDevice(device)) {
            return Error::invalid_address;
        }
        this->deviceHeadNo = numbers.match(memoryAddress).captured();//extract the number of the (first) data word for later use
    }
    else {
        return Error::invalid_address;
    }

    if (command ){

        if( !qCeil(format.fromAsciiToHex(type,data.toUtf8()).length()/4))
            return Error::no_data_provided;

        if (type == BOOL){
            if( !test_bit(QString::number(bitNo) , data, format))
            {
                return Error::invalid_data_provided;
            }

        }else if (!test(type,data,format))
        {
            qWarning () << "here" << type << data ;
            return Error::invalid_data_provided;
        }
    }

    return Error::no_error;
}

QByteArray DataItemValidator::errorToString(int error)
{
    switch (error)
    {
    case  no_error:
        return "no error";
    case dataType_not_boolean:
        return "dataType not boolean";
    case invalid_address:
        return "invalid address";
    case data_lenght_invalid:
        return "data lenght invalid";
    case invalid_data_provided:
        return "invalid data provided";
    case no_data_provided:
        return "no data provided";
    case subheader_command:
        return "Codes for command/response type of subheader are not within the specifications (00 to 05H, 13 to 16H).";
    case ascii_code_not_enabled:
        return "ASCII code data that cannot be converted to binary code was received from an external device.";
    case device_designation:
        return "Device designation from the external side is incorrect.";
    case number_of_points:
        return "Correct the designated points or device number.";
    case head_device_number:
        return "Head device number is set outside the allowable range.";
    case PLC_id:
        return "PC number designated was not 'FF'.";
    case ethernet_communication:
        return "Poor communication between the Ethernet adapter and the PLC";
    case remote_error:
        return "RUN/STOP not accessible.";
    case monitor_time_overflow:
        return "Communication time monitoring timer value.";
    case 0x4B00:
    case 0xC080:
        return  "Device id incorect";
    case 0x4A00:
        return  "Device or network id incorect";
    case 0xC050:
        return "Network id incorect";
    case 0xC051:
        return "Device code/head incorect";
    case 0xC058:
        return "memory points and data lenght mismatch";
    case unknown_error:
    default:
        return "unknown error";
    }
}
