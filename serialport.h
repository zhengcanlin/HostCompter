#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "pointset.h"

#include <QObject>
#include <QString>
#include <QVector>

#include <QSerialPort>
#include <QSerialPortInfo>


class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    void SetBCD(QString PortName,QVector<int>& bcd);

    void OpenPortSlot();
    void ClosePortSlot();
    PointSet GetPointSet();

    bool CRC(QByteArray m_ByteArray);
public slots:
    void ReadBuffSlot();
private:
    QSerialPort *m_SerialPort;
    QVector<QByteArray> ReadBuf;
    PointSet m_PointSet;
private:
    char FrameHead1=(char)(204);     //0xcc
    char FrameHead2=(char)(221);     //0xdd
    char Type_B=(char)(171);         //0xab
    char Type_T=(char)(208);         //0xcd
};

#endif // SERIALPORT_H
