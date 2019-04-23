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
    uint16_t CRC16(QByteArray m_ByteAarray,uint16_t ByteArraySize);
    bool CRC(QByteArray m_ByteArray);

    bool IFOpen();
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

    int FrameSum=0;
    int ErrorFrame=0;
};

#endif // SERIALPORT_H
