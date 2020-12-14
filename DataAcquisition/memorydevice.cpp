#include "memorydevice.h"

/*
 *  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    |       Device name                         |    Symbol   |  Type |  Representation| E4 |     E1         |
    |++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|
    |  Input                                    |   X        |  Bit   |  Hexadecimal   | X* |    5820H       |
    |  Output                                   |   Y        |  Bit   |  Hexadecimal   | Y* |    5920H       |
    |  Internal relay                           |            |        |                |    |                |
    |  (include in latch relay and step relay)  |   M/L/S    |  Bit   |  Decimal       | M* |    4D20H       |
    |  Annunciator                              |   F        |  Bit   |  Decimal       | F* |    4620H       |
    |  Link relay                               |   B        |  Bit   |  Hexadecimal   | B* |    4220H       |
    |  Timer Current value                      |   T        |  Word  |  Decimal       | TN |    544EH       |
    |  Timer Contact                            |   T        |  Bit   |  Decimal       | TS |    5453H       |
    |  Timer Coil                               |   T        |  Bit   |  Decimal       | TC |    5443H       |
    |  Counter Current value                    |   C        |  Word  |  Decimal       | CN |    434EH       |
    |  Counter Contact                          |   C        |  Bit   |  Decimal       | CS |    4353H       |
    |  Counter Coil                             |   C        |  Bit   |  Decimal       | CC |    4343H       |
    |  Data register                            |   D        |  Word  |  Decimal       | D* |    4420H       |
    |  Link register                            |   W        |  Word  |  Hexadecimal   | W* |    5720H       |
    |  File register                            |   R        |  Word  |  Decimal       | R* |    5220H       |
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


MemoryDevice::MemoryDevice()
{
    E1.insert("X",  "5820");
    E1.insert("Y",  "5920");
    E1.insert("F",  "4D20");
    E1.insert("L",  "4620");
    E1.insert("B",  "4220");
    E1.insert("TN", "544E");
    E1.insert("TS", "5453");
    E1.insert("TC", "5443");
    E1.insert("CN", "434E");
    E1.insert("CS", "4353");
    E1.insert("CC", "4343");
    E1.insert("D",  "4420");
    E1.insert("W",  "5720");
    E1.insert("R",  "5220");


    E3.insert("X",  "X*");
    E3.insert("Y",  "Y*");
    E3.insert("F",  "F*");
    E3.insert("M",  "M*");
    E3.insert("L",  "L*");
    E3.insert("B",  "B*");
    E3.insert("TN", "TN");
    E3.insert("TS", "TS");
    E3.insert("TC", "TC");
    E3.insert("CN", "CN");
    E3.insert("CS", "CS");
    E3.insert("CC", "CC");
    E3.insert("D",  "D*");
    E3.insert("W",  "W*");
    E3.insert("R",  "R*");

    E3B.insert("X",  "9C");
    E3B.insert("Y",  "9D");
    E3B.insert("M",  "90");
    E3B.insert("F",  "92");
    E3B.insert("L",  "93");
    E3B.insert("B",  "A0");
    E3B.insert("TN", "C2");
    E3B.insert("TS", "C1");
    E3B.insert("TC", "C0");
    E3B.insert("CN", "C5");
    E3B.insert("CS", "C4");
    E3B.insert("CC", "C3");
    E3B.insert("D",  "A8");
    E3B.insert("W",  "B4");
    E3B.insert("R",  "AF");


    wordDevice.insert("TN");
    wordDevice.insert("CN");
    wordDevice.insert("D");
    wordDevice.insert("W");
    wordDevice.insert("R");

    bitDevice.insert("X");
    bitDevice.insert("Y");
    bitDevice.insert("M");
    bitDevice.insert("L");
    bitDevice.insert("S");
    bitDevice.insert("F");
    bitDevice.insert("B");
    bitDevice.insert("TC");
    bitDevice.insert("TS");
    bitDevice.insert("CC");
    bitDevice.insert("CS");
}

bool MemoryDevice::isWordDevice(QString device){
    if (wordDevice.contains(device)) {
        return true;
    }

    return false;
}

bool MemoryDevice::isBitDevice(QString device){
    if (bitDevice.contains(device)) {
        return true;
    }

    return false;
}
