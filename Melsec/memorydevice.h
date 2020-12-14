#ifndef MEMORYDEVICE_H
#define MEMORYDEVICE_H
#include <QMap>
#include <QSet>

class MemoryDevice
{
public:
   MemoryDevice();
   QMultiMap <QString,QString> E1, E3, E3B;

   /*!
    * \brief isWordDevice checks that the smallest data unit accessible for the passed PLC memory device (aka area) is a word (16 bits)
    * \param device
    * \return the passed parameter is registered as a word device
    */
   bool isWordDevice(QString device);

   /*!
    * \brief isBitDevice  checks that the smallest data unit accessible for the passed PLC memory device (aka area) is a bit
    * \param device
    * \return
    */
   bool isBitDevice(QString device);
   QSet<QString> wordDevice;
   QSet<QString> bitDevice;
};

#endif // MEMORYDEVICE_H
