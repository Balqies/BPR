#ifndef DATAFORMATER_H
#define DATAFORMATER_H
#include <QtCore>

#define BIT_SET(a,b)((a)|=(1U<<(b)))
#define BIT_CLEAR(a,b)((a)&=~(1U<<(b)))
#define BIT_FLIP(a,b)((a)^=(1U<<(b)))
#define BIT_CHECK(a,b)(!!((a)&(1U<<(b))))
#define READ 0
#define WRITE 1

enum DataTypes{ BOOL, INT16, INT32, INT64, UINT16, UINT32, UINT64, BCD16,
                BCD32, BCD64, REAL, LREAL, WORD, UNKNOWN, ASCII};
// here data from dataItem is converted into PLC format and vice versa
class DataFormater
{
public:

    /*!
     * \brief DataFormater is resposible with the formatting user data values to and from plc raw data(hexadecimal)
     */
    DataFormater();

    /*!
     * \brief dataTypesToString returs a  human readable string description of a data type
     * \param type PLC data type
     * \return string
     */
    QString dataTypesToString(DataTypes type);

    /*!
     * \brief fromAsciiToHex formats a string containing a value into hexadecimal raw data
     * \param type of the data in the input string
     * \param data string containing a data value
     * \return hexadecimal number as string
     */
    QString fromAsciiToHex(DataTypes type, QString data);

    /*!
     * \brief fromHextoAscii formats a string of raw data expressed as a hexadecimal value into a standard data type
     * \param type of the data in the return string
     * \param data string of raw data
     * \return standard data type as string
     */
    QByteArray fromHextoAscii(DataTypes type, QString data);

    /*!
     * \brief bitFromPLCtoItem reads the binary value of a word at a given bit index
     * \param data hexadecimal word as string
     * \param bitNo index of the bit to be read
     * \return
     */
    QString bitFromPLCtoItem(QString data, QString bitNo);

    /*!
     * \brief bitFromItemtoPLC sets the binary value of a given word at a given bit index
     * \param data the word that is to be changed
     * \param bitNo the index aof the bit to be cahanged
     * \param bit the new value of the bit
     * \return
     */
    QString bitFromItemtoPLC(QString data, QString bitNo, QString bit);

    /*!
     * \brief invertByteArray inverts a byte array
     * \param dataFromPLC input
     * \return inverted byte array
     */
    QByteArray invertByteArray (QByteArray dataFromPLC);

    QByteArray getSizeInWords(DataTypes type);
};

#endif // DATAFORMATER_H
