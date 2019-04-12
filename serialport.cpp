#include "serialport.h"


SerialPort::SerialPort():
    m_SerialPort(new QSerialPort)
{

}

//设置串口BCD，由串口类调用
//每次转换串口时，都需要先关闭串口，调用该函数之后，才能重新打开
void SerialPort::SetBCD(QString PortName, QVector<int>& bcd){
    this->m_SerialPort->setPortName(PortName);
    int m_BaudRate=bcd.at(0);
    int m_Parity=bcd.at(1);
    int m_DataBit=bcd.at(2);
    int m_StopBot=bcd.at(3);
    switch (m_BaudRate){
    case 1200:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        this->m_SerialPort->setBaudRate(QSerialPort::Baud38400);
        break;
    }

    switch (m_Parity){
    case 0:
        this->m_SerialPort->setParity(QSerialPort::NoParity);
        break;
    case 1:
        this->m_SerialPort->setParity(QSerialPort::OddParity);
        break;
    case 2:
        this->m_SerialPort->setParity(QSerialPort::EvenParity);
        break;
    }

    switch (m_DataBit) {
    case 5:
        this->m_SerialPort->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        this->m_SerialPort->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        this->m_SerialPort->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        this->m_SerialPort->setDataBits(QSerialPort::Data8);
        break;
    }

    switch (m_StopBot){
    case 0:
        this->m_SerialPort->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        this->m_SerialPort->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        this->m_SerialPort->setStopBits(QSerialPort::TwoStop);
        break;
    }

}

//开启同时可读写串口
void SerialPort::OpenPortSlot(){
    this->m_SerialPort->open(QIODevice::ReadWrite);
}

//关闭串口
void SerialPort::ClosePortSlot(){
    this->m_SerialPort->clear();
    this->m_SerialPort->close();
}
SerialPort::~SerialPort(){
    delete m_SerialPort;
}
