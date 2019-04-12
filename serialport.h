#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QString>
#include <QVector>

#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort
{
public:
    SerialPort();
    ~SerialPort();

    void SetBCD(QString PortName,QVector<int>& bcd);

    void OpenPortSlot();
    void ClosePortSlot();

private:
    QSerialPort *m_SerialPort;
};

#endif // SERIALPORT_H
