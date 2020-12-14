#include "dataformater.h"

DataFormater::DataFormater(){}

QString DataFormater::dataTypesToString(DataTypes type)
{

    switch (type)
    {
    case DataTypes::BOOL:
        return "Bit";
    case DataTypes::INT16:
        return "Signed 16 bits Integer";
    case DataTypes::INT32:
        return "Signed 32 bits Integer";
    case DataTypes::INT64:
        return "Signed 64 bits Integer";
    case DataTypes::UINT16:
        return "Unsigned 16 bits Integer";
    case DataTypes::UINT32:
        return "Unsigned 32 bits Integer";
    case DataTypes::UINT64:
        return "Unsigned 64 bits Integer";
    case DataTypes::BCD16:
        return "Unsigned 16 bits BCD";
    case DataTypes::BCD32:
        return "Unsigned 32 bits BCD";
    case DataTypes::BCD64:
        return "Unsigned 64 bits BCD";
    case DataTypes::REAL:
        return "Signed floating point real number";
    case DataTypes::LREAL:
        return "Signed double precision floating point real number";
    case DataTypes::WORD:
        return "Hexadecimal 16 bits - word";
    default:
        return "Unknown Data Type";
    }
}


//convert user input data to hexadecimal number for PLC memory storage
QString DataFormater::fromAsciiToHex(DataTypes type, QString data)
{
    switch (type)
    {
    case DataTypes::INT16:
    {
        auto ascii = QString::number(uint16_t(data.toShort(nullptr,10)),16).toUpper();
        while (ascii.length()<4) ascii = "0"+ascii; //lenght of string is size of type in bits divided by size of char in bits. Fx.: 16/4 = 4
        return ascii;
    }

    case DataTypes::INT32:
    {
        auto ascii = QString::number(uint32_t(data.toLong(nullptr,10)),16).toUpper();
        while (ascii.length()<8) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::INT64:
    {
        auto ascii = QString::number(uint64_t(data.toLongLong(nullptr,10)),16).toUpper();
        while (ascii.length()<16) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::UINT16:
    {
        auto ascii = QString::number(uint16_t(data.toUShort(nullptr,10)),16).toUpper();
        while (ascii.length()<4) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::UINT32:
    {
        auto ascii = QString::number(uint16_t(data.toULong(nullptr,10)),16).toUpper();
        while (ascii.length()<8) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::UINT64:
    {
        auto ascii = QString::number(uint16_t(data.toULongLong(nullptr,10)),16).toUpper();
        while (ascii.length()<16) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::BCD16:
    {
        auto ascii = QString::number(uint16_t(data.toUShort(nullptr,16)),16).toUpper();
        while (ascii.length()<4) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::BCD32:
    {
        auto ascii = QString::number(uint16_t(data.toUShort(nullptr,16)),16).toUpper();
        while (ascii.length()<8) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::BCD64:
    {
        auto ascii = QString::number(uint16_t(data.toUShort(nullptr,16)),16).toUpper();
        while (ascii.length()<16) ascii = "0"+ascii;
        return ascii;
    }

    case DataTypes::REAL:
    {
        float real = data.toFloat(nullptr);
        qWarning()<<real;
        uint32_t decimal = 0;
        memcpy(&decimal,&real,sizeof (real));
        return QString::number(decimal,16).toUpper();
    }

    case DataTypes::LREAL:
    {
        double real = data.toDouble(nullptr);
        int64_t decimal = 0;
        memcpy(&decimal,&real,sizeof (real));
        return QString::number(decimal,16).toUpper();
    }

    case DataTypes::WORD:
        return data;
    case DataTypes::ASCII:
    {
        QString output = "";
        foreach (QChar a, data)
        {
            output = output.prepend(QString::number(int(a.toLatin1()),16)) ;
        }

        while (output.length()%4)
            output = (QString::number(0,16))+output;
        return output.toUpper();
    }

    default:return "Unknown Data Type";
    }
}

//convert PLC data from hex format to user format
QByteArray DataFormater::fromHextoAscii(DataTypes type, QString data)
{
    switch (type) {
    /*  DataTypes::BOOL: since a third argument is required it is handled in a separate function -->bitFromPLCtoItem(QByteArray in, ushort bitNo)*/
    case DataTypes::INT16:
    {
        return  QString::number(int16_t(data.toUShort(nullptr,16))).toUtf8() ;
    }
    case DataTypes::INT32:
    {
        return  QString::number(int32_t(data.toULong(nullptr,16))).toUtf8() ;
    }
    case DataTypes::INT64:
    {
        return  QString::number(int64_t(data.toULongLong(nullptr,16))).toUtf8() ;
    }
    case DataTypes::UINT16:
    {
        return  QString::number(uint16_t(data.toUShort(nullptr,16))).toUtf8() ;
    }
    case DataTypes::UINT32:
    {
        return  QString::number(uint32_t(data.toULong(nullptr,16))).toUtf8() ;
    }
    case DataTypes::UINT64:
    {
        return  QString::number(uint64_t(data.toULongLong(nullptr,16))).toUtf8() ;
    }
    case DataTypes::BCD16:
    {
        return QString::number(uint16_t(data.toUShort(nullptr,16)),16).toUpper().toUtf8();
    }
    case DataTypes::BCD32:
    {
        return QString::number(uint32_t(data.toULong(nullptr,16)),16).toUpper().toUtf8();
    }
    case DataTypes::BCD64:
    {
        return QString::number(uint64_t(data.toULongLong(nullptr,16)),16).toUpper().toUtf8();
    }
    case DataTypes::REAL:
    {
        uint32_t bits= data.toUInt(nullptr,16);
        float temp;
        memcpy(&temp,&bits,sizeof (bits));
        return  QString::number(double(temp), 'g', 5).toUtf8(); // format as [-]x.xxxx trailing zeroes are omitted
    }
    case DataTypes::LREAL:
    {
        uint64_t bits= data.toULongLong(nullptr,16);
        double temp;
        memcpy(&temp,&bits,sizeof (bits));
        return  QString::number(temp, 'g', 4).toUtf8(); // format as [-]x.xxxx trailing zeroes are omitted
    }
    case DataTypes::WORD:
        return data.toUtf8(); //"Hexadecimal 16 bits - words"
    case DataTypes::ASCII:
    {
        QByteArray byteArrayOut, byteArrayIn = data.toUtf8();
        for (int i = 0; i <data.length(); ++i) {
            char firstCharNumber ;
            char secondCharNumber;
            if (i<data.size()) {
                firstCharNumber = byteArrayIn[i];
                if (++i<data.length()) {
                    secondCharNumber= byteArrayIn[i];
                } else {
                    firstCharNumber = '\0';
                    secondCharNumber = '\0';
                }
                byteArrayOut = char((QString(firstCharNumber) + (secondCharNumber)).toUInt(nullptr,16)) + byteArrayOut;  // make a character from 2 digit number and add it to string
            }
        }
        return byteArrayOut;
    }
    default:return "Unknown Data Type";
    }
}

QString DataFormater::bitFromPLCtoItem(QString data, QString bitNo)
{
    return QString::number(BIT_CHECK(QString(data).toUShort(nullptr,16), bitNo.toUShort()));
}
QString DataFormater::bitFromItemtoPLC(QString data, QString bitNo, QString bit)
{
    ushort intFromPlc = data.toUShort(nullptr,16);
    if (bit.toUShort())
        return QString::number(BIT_SET(intFromPlc, bitNo.toUShort()),16).toUpper();
    else
        return QString::number(BIT_CLEAR(intFromPlc, bitNo.toUShort()),16).toUpper();
}

QByteArray DataFormater::invertByteArray(QByteArray dataFromPLC)
{
    QByteArray tempString = "";
    foreach (char c, dataFromPLC) tempString = c + tempString;
    return tempString;
}

QByteArray DataFormater::getSizeInWords(DataTypes type)
{
    QByteArray size = "0";
    switch (type)
    {
    case DataTypes::BOOL:
    case DataTypes::INT16:
    case DataTypes::UINT16:
    case DataTypes::BCD16:
    case DataTypes::WORD:
            size = "1";
        break;
    case DataTypes::INT32:
    case DataTypes::UINT32:
    case DataTypes::BCD32:
    case DataTypes::REAL:
            size = "2";
        break;
    case DataTypes::INT64:
    case DataTypes::UINT64:
    case DataTypes::BCD64:
    case DataTypes::LREAL:
        size = "4";
        break;
    default:
        break;
    }
    return size;
}
