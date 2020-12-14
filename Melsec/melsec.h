#ifndef MELSEC_H
#define MELSEC_H
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include "dataformater.h"
#include "plugin/plugininterface.h"
#include "plugin/plugininstanceinterface.h"
#include "socket.h"
#include "frame.h"
#include "dataitemvalidator.h"


class Melsec : public QObject, public SIAInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SIAInterface_IID)
    Q_INTERFACES(SIAInterface)
public:
    Melsec();
    /*!
     * \brief init
     * Table structure of the data logging.
     * Item table structure. This could contain tag address
     * Device table structure for adding the peripheral ports. This could contain ports, baudrate etc.
     * Settings for the device userdefined fields to be able to set baudrate, parity etc...
     * \return true
     */
    bool init() override;

    /*!
     * \brief Gets device info from log list, iterates trough the list of data items in the log list
     * and for each data item retrieves the the memory address and data type needed to form a
     * read command  for the PLC that will retrieve a value that will overwrite the existent one.
     * \param Loglist is a pointer to a log list provided by SIA
     * \return
     */
    bool readData(LogList *Loglist) override;

    /*!
     * \brief getEventData - unimplemented
     * \param Loglist is a pointer to a log list provided by SIA
     * \return
     */
    bool getEventData(LogList *Loglist) override;

    /*!
     * \brief logCallback - unimplemented
     * \param Loglist is a pointer to a log list provided by SIA
     * \return
     */
    bool logCallback(LogList *Loglist) override;

    /*!
     * \brief writeData
     * \brief Gets device info from log list, iterates trough the list of data items in the log list
     * and for each data item retrieves the the value, memory address and data type needed to form a
     * write command  for the PLC that will push the value from the item to the PLC memory
     * \param Loglist is a pointer to a log list provided by SIA
     * \return
     */
    bool writeData(LogList *Loglist) override;

    /*!
     * \brief stopPlugin
     * \return
     */
    bool stopPlugin() override;

//    bool Melsec::event(QEvent *event) override;

//    bool Melsec::eventFilter(QObject *watched, QEvent *event) override;

    int connectDevice(DeviceInstancePlugin *device);
    bool makeSocket(DeviceInstancePlugin *device);
    Socket getDeviceConnection(DeviceInstancePlugin *device);
    QList<Socket> sockets;
    QMap<int, QString> connections;

    PluginInterface interface;

private:
    void disconnectFromDev();
    int makeFrame(int command, DeviceInstancePlugin device, DataItem dataItem, QByteArray *sendBuff);
    bool hasConnection(DeviceInstancePlugin *device);
    QByteArray makeBinaryFrame(QByteArray frame);
    QByteArray sendBuffer;
    QByteArray replyBuffer;
    QByteArray dataFromPLC;
    Socket tcp;
    DataFormater formater;
    DataItemValidator checkData;
    Frame frame;

};
#endif // MELSEC_H
