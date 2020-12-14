/*****          Commands and Function List for 1E Frame           ***************************************************************************
     +-----------------+-----------------------------------+-------------+---------+--------------------------------------------------------+
     |  Function  definitions for 1E frame                 |          Subheader    |                                                        |
     |  (   Ascii frame  00H = "00"                        +-----------+-----------+         Reference                                      |
     |      Binary frame 00H = 0x00   )                    | Request   | Response  |                                                        |
     |                                                     | message   | message   |                                                        |
     +-----------------+-----------------------------------+-----------------------+--------------------------------------------------------+
     | Device memory:  |     Batch read:     | Bit units   |   00H     |   80H     |   Reads bit devices (X, Y, M, etc.) in 1-point units.  |
     |                 |                     +-------------+-----------+-----------+--------------------------------------------------------+
     |                 |                     | Word units  |   01H     |   81H     |   Reads bit devices (X, Y, M, etc.) in 16-point units. |
     |                 |                     |             |           |           |   Reads word devices (D, T, C, etc.) in 1-point units. |
     |                 +---------------------+-------------+-----------+-----------+--------------------------------------------------------+
     |                 |     Batch write:    | Bit units   |   02H     |   82H     |   Writes bit devices (X, Y, M, etc.) in 1-point units. |
     |                 |                     +-------------+-----------+-----------+--------------------------------------------------------+
     |                 |                     | Word units  |   03H     |   83H     |   Writes bit devices (X, Y, M, etc.) in 16-point units.|
     |                 |                     |             |           |           |   Writes word devices (D, T, C, etc.) in 1-point units |
     +-----------------+---------------------+-------------+-----------+-----------+--------------------------------------------------------+
     |   Extended file |     Batch read:                   |   17H     |   97H     |   Reads extended file register (R) in 1-point units.   |
     |    register     |-----------------------------------+-----------+-----------+--------------------------------------------------------+
     |                 |     Batch write:                  |   18H     |   98H     |   Writes extended file register (R) in 1-point units.  |
     +-----------------+---------------------+-------------+-----------+-----------+--------------------------------------------------------+
********        https://dl.mitsubishielectric.com/dl/fa/document/manual/plc/sh080008/sh080008y.pdf   Ch.18.3 *******************************/


/*****          End codes (completion codes) returned to an external device during data communication for 1E Frame        *******************
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     | End code     |            Description                                             |             Corrective action                    |
     |(hexadecimal) |                                                                    |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |    00H       |         Normal completion                                          |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              |                                                                    |  * Check and correct command/ response           |
     |              |                                                                    |    type set by an external device. (The          |
     |              |                                                                    |    Ethernet adapter automatically adds           |
     |              |   Codes for command/response type of subheader are not within the  |    command/ response type; the user does         |
     |              |   specifications (00 to 05H, 13 to 16H).                           |    not need to set these.)                       |
     |              |                                                                    |                                                  |
     |    50H       |                                                                    |  * Check and correct the data length.            |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              | When "ASCII code communication" is selected in the [Communication  |  Check and correct the send data of the external |
     |              | data code settings] of operational setting parameters of GX Works2,|  device.                                         |
     |              | ASCII code data that cannot be converted to binary code was        |                                                  |
     |    54H       | received from an external device.                                  |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |    56H       | Device designation from the external side is incorrect.            |  Correct the device designated.                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              |  * The number of points for a command designated by an external    |                                                  |
     |              |    device exceeds the maximum number of processing points for each |                                                  |
     |              |    processing (number of processes that can be executed per        |                                                  |
     |              |    communication).                                                 |                                                  |
     |              |                                                                    |                                                  |
     |              |  * Head device number to the designated points exceeds the maximum |  Correct the designated points or device number. |
     |              |    addresses (device number).                                      |                                                  |
     |              |                                                                    |                                                  |
     |              |  * When performing batch read/write operations on C200 to C255,    |                                                  |
     |              |    the number of device points was designated with an odd number.  |                                                  |
     |              +--------------------------------------------------------------------+--------------------------------------------------+
     |              |   * Byte length of a command does not conform to the               |                                                  |
     |              |     specifications.                                                |  Check the data length of the command and        |
     |              |   * When writing data, the set number of points for data to be     |  adjust the data setting.                        |
     |    57H       |      written is different from the number of points specified      |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              | Head device number of a command designated by an external device   |  Designate the appropriate values within the     |
     |              | is set outside the allowable range.                                |  range that are allowed for each processing.     |
     |              +--------------------------------------------------------------------+--------------------------------------------------+
     |              |  * A word device is designated in a command for bit devices.       |  Correct the command or the designated device.   |                                             |
     |              |  * The head number of bit devices is designated by a value other   |                                                  |
     |              |    than a multiple of 16 in a command for word devices.            |                                                  |
     |    58H       |                                                                    |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              |  * The PLC and the Ethernet adapter cannot communicate.            |   Fix the faulty parts by referring to the       |
     |              |  * The PLC cannot process requests from an external device.        |   abnormal codes appended to the end codes       |
     |              +--------------------------------------------------------------------+--------------------------------------------------+
     |              | Error code | Error        | Description of error                   |   Corrective action                              |
     |              |  (hex)     |              |                                        |                                                  |
     |              +------------+--------------+----------------------------------------+--------------------------------------------------+
     |              |   10H      | PC no. error | PC number designated was not "FF".     |    Set the PC number to "FF".                    |
     |              +------------+--------------+----------------------------------------+--------------------------------------------------+
     |              |            | Mode error   | Poor communication between the         |  Communicate again. If an error occurs           |
     |              |            |              | Ethernet adapter and the PLC           |  again, check noise, etc. and replace the        |
     |              |            |              | * After the Ethernet adapter receives  |  Ethernet adapter, then communicate again.       |
     |              |            |              |   a request successfully from an       |                                                  |
     |              |            |              |   external device, the Ethernet adapter|                                                  |
     |              |            |              |   and the PLC could not communicate for|                                                  |
     |              |   11H      |              |   some reason (noise, etc.).           |                                                  |
     |              +------------+--------------+----------------------------------------+--------------------------------------------------+
     |              |            | Remote error |  RUN/STOP not accessible.              | Check whether the ERROR (ERR) LED of             |
     |              |            |              |  * The PLC main unit status is error.  | the PLC main unit is on or flickering            |
     |              |            |              |                                        | Check the contents of the error and              |
     |    5BH       |   18H      |              |                                        | remove the cause.                                |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
     |              |  Communication time between the Ethernet adapter and the PLC       |  Increase the monitoring timer value.            |
     |              |  exceeded PLC monitoring timer value. Increase the monitoring      |                                                  |
     |    60H       |  timer value.                                                      |                                                  |
     +--------------+--------------------------------------------------------------------+--------------------------------------------------+
*** https://www.allied-automation.com/wp-content/uploads/2015/02/MITSUBISHI_FX3U-ENET-ADP-Ethernet-Users-Manual.pdf  Ch. 10.3.2, 10.3.3  ***/


/*
 *  3E/4E and 3C/4C frames
 *
 * COMMANDS:
 *  read single block:      0401
 *  read multiple blocks:   0406
 *  write single block:     1401
 *  write multiple blocks:  1406
 *
 * SUBCOMMANDS:
 *  0000  _|-> access bit devices (X, Y, M) in 16-point units.
 *         |-> access word devices (D, R, T, C) in 1-point units.
 *
 *  0001   --> access bit devices (X, Y, M) in 1-point unit.

 *  1E frame
 *
 * COMMANDS:
 *  00  --> read bit devices (X, Y, M, S, T, C) in 1-point units.
 *
 *  01  --> read word devices (D, R, T, C) in 1-point units.
 *      --> read bit devices (X, Y, M, S, T, C) in 16-point units.
 *
 *  02  --> write bit devices (X, Y, M, S, T, C) in 16-point units.
 *
 *  03  --> write word devices (D, R, T, C) in 1-point units.
 *      --> write bit devices (X, Y, M, S, T, C) in 16-point units.


*/

// to add: " A specified command or subcommand is wrong" from: 0x8A 0x50


#ifndef FRAME_H
#define FRAME_H
#include <QCoreApplication>
#include "memorydevice.h"
#include "dataitemvalidator.h"
#define ASCII_1E   1
#define BINARY_1E  2
#define ASCII_3E   3
#define BINARY_3E  4
#define ASCII_4E   5
#define BINARY_4E  6
#define ASCII_1C   7
#define ASCII_2C   8
#define ASCII_3C   9
#define ASCII_4C  10
#define BINARY_4C 11
class Frame
{
public:
    Frame();
    QByteArray fixedVAlFor1E = "00";
    QString subheader_3E = "5000";
    QString subheader_4E = "5400";
    QString def_RDM_IO = "03FF"; // default Request destination module I/O No.
    QString def_RDM_S = "00"; // default Request destination module station No.
    MemoryDevice device;

    QByteArray make(QString destination,
                    QByteArray monitorTimer,
                    int genericCmd,
                    QByteArray devCode,
                    QByteArray devHeadNo,
                    QByteArray devNoOfPoints,
                    QByteArray data,
                    int frameType ) ;

    /*!
     * \brief getAsciiResponseFromBinary converts each byte in byte array form his hexadecimal value to an ASCII tuple
     * i.e. 0xa5 -> "A5"
     * \param binaryResponse
     * \return
     */
    QByteArray getAsciiResponseFromBinary(QByteArray binaryResponse);
    int decodeResponse(int  frameType, QByteArray frame, QByteArray response, QByteArray *data);
    QByteArray frameSpecificCmd(int userCommand, QByteArray deviceHeadNo, int frameType);
    QByteArray mcHeadNo(QByteArray userDeviceHeadNo);
    QByteArray e3HeadNo(QByteArray userDeviceHeadNo);
    QByteArray e1DevCode(QByteArray userDevCode);
    QByteArray e3DevCode(QByteArray userDevCode);
    QByteArray e3bDevCode(QByteArray userDevCode);
    QByteArray mcMonitorTimer(QByteArray userMonitorTimer);
    QByteArray frameSpecificCommand(int userCommand, QByteArray deviceHeadNo);
    QByteArray e1DestinationNo(int userDestination);
    QByteArray e3DestinationNo(int userDestination);
    QByteArray mcDataLenght(QByteArray itemData);
    QMap<QString, QString> deviceCodesMap;
    QByteArray toBinary(QByteArray chars);
    QByteArray toBinaryData(QByteArray chars);
    QByteArray subheader3E(QString destination, bool isBinary);
    QByteArray subheader4E(QString destination, bool isBinary);
    QByteArray message3E(QByteArray monitorTimer, int genericCmd, int frameType, QByteArray devCode,QByteArray devHeadNo, QByteArray devNoOfPoints, QByteArray data, bool isBinary );
    QByteArray serialNo();
    int decode1EResponse(int frameType, QByteArray frame, QByteArray response, QByteArray *data);
    int decode3EResponse(int frameType, QByteArray response, QByteArray *data);
private:



};
#endif // FRAME_H
