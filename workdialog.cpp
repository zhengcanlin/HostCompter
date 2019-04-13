#include "workdialog.h"

struct workdialog::control_s{
    QLabel *label_Change;
    QLabel *label_port;
    QLabel *label_BaudRate;
    QLabel *label_Parity;
    QLabel *label_Data;
    QLabel *label_StopBit;

    QComboBox *combobox_Change;
    QComboBox *combobox_port;
    QComboBox *combobox_BaudRate;
    QComboBox *combobox_Parity;
    QComboBox *combobox_Data;
    QComboBox *combobox_StopBit;


    QPushButton *openPortButton;
    QPushButton *closePortButton;
    QPushButton *setPortButton;
    QPushButton *clearButton2;
    QPushButton *clearButton1;
    QPushButton *sendDataButton;


    QTextEdit *show_the_data;
    QTextEdit *send_data;


    control_s(){
        label_BaudRate=new QLabel(tr("波特率"));
        label_Parity=new QLabel(tr("奇偶校验"));
        label_StopBit=new QLabel(tr("停止位"));
        label_Change=new QLabel(tr("监控对象"));
        label_Data=new QLabel(tr("数据位"));
        label_port=new QLabel(tr("串口号"));

        combobox_BaudRate=new QComboBox;
        combobox_Parity=new QComboBox;
        combobox_StopBit=new QComboBox;
        combobox_Change=new QComboBox;
        combobox_Data=new QComboBox;
        combobox_port=new QComboBox;


        clearButton1=new QPushButton(tr("清除发送框"));
        clearButton2=new QPushButton(tr("清除打印框"));
        sendDataButton=new QPushButton(tr("发送"));
        openPortButton=new QPushButton(tr("打开串口"));
        closePortButton=new QPushButton(tr("关闭串口"));
        setPortButton=new QPushButton(tr("设置参数"));


        show_the_data=new QTextEdit;
        send_data=new QTextEdit;

    }
    ~control_s(){
        delete label_BaudRate;
        delete label_Parity;
        delete label_StopBit;
        delete label_Change;
        delete label_Data;
        delete label_port;

        delete combobox_BaudRate;
        delete combobox_Parity;
        delete combobox_StopBit;
        delete combobox_Change;
        delete combobox_Data;
        delete combobox_port;

        delete clearButton1;
        delete clearButton2;
        delete sendDataButton;
        delete openPortButton;
        delete closePortButton;
        delete setPortButton;

        delete show_the_data;
        delete send_data;
    }
};
workdialog::workdialog(QWidget *parent)
    : QWidget(parent),
      tool_box(new control_s),
      m_ValueLabel(new QLabel),
      timers(new QTimer),
      readtimer(new QTimer),
      SerialServer(new SerialPort)
{
    initChart();
    InitLayout();
    InitCombobox();
    InitButton();
    this->resize(800,600);
}

void workdialog::initChart(){
    this->m_chart=new QChart();
    this->m_scatterSeries_B=new QScatterSeries;
    this->m_scatterSeries_T=new QScatterSeries;

    this->m_scatterSeries_B->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    this->m_scatterSeries_B->setMarkerSize(10);
    this->m_scatterSeries_T->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    this->m_scatterSeries_T->setMarkerSize(10);
    this->m_scatterSeries_T->setColor(Qt::lightGray);

    this->m_chart->addSeries(this->m_scatterSeries_B);
    this->m_chart->addSeries(this->m_scatterSeries_T);
    this->m_chart->createDefaultAxes();

    this->m_axisX=new QValueAxis;
    m_axisX->setRange(0,100);
    m_axisX->setGridLineVisible(true);
    m_axisX->setTickCount(50);

    this->m_axisY=new QValueAxis;
    m_axisY->setRange(0,100);
    m_axisY->setGridLineVisible(true);
    m_axisY->setTickCount(50);

    m_chart->setAxisX(m_axisX,m_scatterSeries_B);
    m_chart->setAxisY(m_axisY,m_scatterSeries_B);
    m_chart->setAxisX(m_axisX,m_scatterSeries_T);
    m_chart->setAxisY(m_axisY,m_scatterSeries_T);

    m_chart->legend()->hide();

    m_chartView=new QChartView;
    m_chartView->setChart(m_chart);

    m_chartView->setVisible(true);
    connect(readtimer,SIGNAL(timeout()),this,SLOT(UpdateChart()));

    connect(m_scatterSeries_B,SIGNAL(hovered(QPointF,bool)),this,SLOT(PointHoverdSlot(QPointF,bool)));
    connect(m_scatterSeries_T,SIGNAL(hovered(QPointF,bool)),this,SLOT(PointHoverdSlot(QPointF,bool)));
}
void workdialog::InitLayout(){
    tool_box->label_Change->setBuddy(tool_box->combobox_Change);
    tool_box->label_port->setBuddy(tool_box->combobox_port);
    tool_box->label_BaudRate->setBuddy(tool_box->combobox_BaudRate);
    tool_box->label_Parity->setBuddy(tool_box->combobox_Parity);
    tool_box->label_Data->setBuddy(tool_box->combobox_Data);
    tool_box->label_StopBit->setBuddy(tool_box->combobox_StopBit);

    //窗口左上角布局管理器
    QFormLayout *left_first_layout=new QFormLayout;
    left_first_layout->addRow(tool_box->label_Change,tool_box->combobox_Change);
    left_first_layout->addRow(tool_box->label_port,tool_box->combobox_port);
    left_first_layout->addRow(tool_box->label_BaudRate,tool_box->combobox_BaudRate);
    left_first_layout->addRow(tool_box->label_Parity,tool_box->combobox_Parity);
    left_first_layout->addRow(tool_box->label_Data,tool_box->combobox_Data);
    left_first_layout->addRow(tool_box->label_StopBit,tool_box->combobox_StopBit);

    //窗口左中布局管理器
    QGridLayout *left_second_layout=new QGridLayout;
    left_second_layout->addWidget(tool_box->openPortButton,0,0);
    left_second_layout->addWidget(tool_box->closePortButton,0,1);
    left_second_layout->addWidget(tool_box->setPortButton,1,0);
    left_second_layout->addWidget(tool_box->clearButton2,1,1);


    //窗口左布局管理器
    QVBoxLayout *left_thrid_layout=new QVBoxLayout;
    left_thrid_layout->addLayout(left_first_layout);
    left_thrid_layout->addLayout(left_second_layout);
    left_thrid_layout->addWidget(tool_box->show_the_data);

    /*
     *  设置左边的布局管理
     *  1-formlayout布局管理器
     *  2-textedit
     */

    QVBoxLayout *right_frist_layout=new QVBoxLayout;
    right_frist_layout->addWidget(tool_box->sendDataButton);
    right_frist_layout->addWidget(tool_box->clearButton1);

    QHBoxLayout *right_second_layout=new QHBoxLayout;
    right_second_layout->addLayout(right_frist_layout,1);
    right_second_layout->addWidget(tool_box->send_data,9);

    QVBoxLayout *right_thrid_layout=new QVBoxLayout;
    right_thrid_layout->addWidget(this->m_chartView,8);
    right_thrid_layout->addLayout(right_second_layout,2);

    QHBoxLayout *main_layout=new QHBoxLayout;
    main_layout->addLayout(left_thrid_layout,1);
    main_layout->addLayout(right_thrid_layout,3);

    tool_box->show_the_data->setReadOnly(true);
    tool_box->clearButton2->setEnabled(false);
    setLayout(main_layout);


}
void workdialog::InitCombobox(){
    QStringList lists;

    lists.clear();

    lists<<tr("1200")<<tr("2400")<<tr("4800")<<tr("9600")<<tr("19200")<<tr("38400");
    this->tool_box->combobox_BaudRate->addItems(lists);
    this->tool_box->combobox_BaudRate->setCurrentText("9600");

    lists.clear();

    lists<<tr("无")<<tr("奇")<<tr("偶");
    this->tool_box->combobox_Parity->addItems(lists);
    this->tool_box->combobox_Parity->setCurrentIndex(0);

    lists.clear();

    lists<<tr("5")<<tr("6")<<tr("7")<<tr("8");
    this->tool_box->combobox_Data->addItems(lists);
    this->tool_box->combobox_Data->setCurrentIndex(0);

    lists.clear();

    lists<<tr("1")<<tr("1.5")<<tr("2");
    this->tool_box->combobox_StopBit->addItems(lists);
    this->tool_box->combobox_StopBit->setCurrentIndex(0);

    lists.clear();

    lists<<tr("AllPoint")<<tr("BaseNode")<<tr("FrameNode");
    this->tool_box->combobox_Change->addItems(lists);
    this->tool_box->combobox_Change->setCurrentIndex(0);

    lists.clear();

    timers->start(50);
    connect(timers,SIGNAL(timeout()),this,SLOT(UpdatePortCom()));
}
void workdialog::InitButton(){

    connect(tool_box->openPortButton,SIGNAL(clicked(bool)),this,SLOT(OpenPort()));

    connect(tool_box->closePortButton,SIGNAL(clicked(bool)),this,SLOT(ClosePort()));

    connect(tool_box->setPortButton,SIGNAL(clicked(bool)),this,SLOT(ClosePort()));

    connect(tool_box->clearButton2,SIGNAL(clicked(bool)),this,SLOT(UpdateEditSlot()));

    connect(tool_box->clearButton1,SIGNAL(clicked(bool)),tool_box->send_data,SLOT(clear()));
}
void workdialog::UpdatePortCom(){
    QList<QSerialPortInfo> SerialPortList;
    QSerialPortInfo *serialportinfo=new QSerialPortInfo;
    SerialPortList=serialportinfo->availablePorts();
    //获取目前可用的串口

    int count_i=0;
    while(count_i<tool_box->combobox_port->count()){
        int count_j;
        for(count_j=0;count_j<SerialPortList.length();count_j++){
            if(tool_box->combobox_port->itemText(count_i)==SerialPortList[count_j].portName()){
                break;
            }
        }
        if(count_j==SerialPortList.length()){
            tool_box->combobox_port->removeItem(count_i);
        }
        else {
            SerialPortList.removeAt(count_j);
            count_i++;
        }
        if(SerialPortList.isEmpty()==true){
            break;
        }
    }
    if(SerialPortList.isEmpty()==false){
        for(int i=0;i<SerialPortList.length();i++){
            tool_box->combobox_port->addItem(SerialPortList[i].portName());
        }
    }
    else{
        while(count_i<tool_box->combobox_port->count()){
            tool_box->combobox_port->removeItem(count_i);
        }
    }
}
void workdialog::UpdateShowEdit(){
    tool_box->show_the_data->append("观察对象："+tool_box->combobox_Change->currentText());
    tool_box->show_the_data->append("使用串口："+tool_box->combobox_port->currentText());
    tool_box->show_the_data->append("波特率："+tool_box->combobox_BaudRate->currentText());
    tool_box->show_the_data->append("奇偶校验："+tool_box->combobox_Parity->currentText());
    tool_box->show_the_data->append("数据位："+tool_box->combobox_Data->currentText());
    tool_box->show_the_data->append("停止位："+tool_box->combobox_StopBit->currentText());
}


//SLOT FUNCTION
void workdialog::OpenPort(){
    QVector<int> bcd;
    QString portname;
    portname=this->tool_box->combobox_port->currentText();

    bcd.push_back(this->tool_box->combobox_BaudRate->currentText().toInt());
    bcd.push_back(this->tool_box->combobox_Parity->currentIndex());
    bcd.push_back(this->tool_box->combobox_Data->currentIndex());
    bcd.push_back(this->tool_box->combobox_StopBit->currentIndex());

    this->SerialServer->SetBCD(portname,bcd);
    this->SerialServer->OpenPortSlot();
        //如果打开成功，每500ms，从串口对象读取点集，然后用画布更新
    if(this->SerialServer->IFOpen()){
        this->readtimer->start(500);
        UpdateShowEdit();
        this->tool_box->clearButton2->setEnabled(true);
    }
}
void workdialog::ClosePort(){
    this->SerialServer->ClosePortSlot();
    this->readtimer->stop();
    this->tool_box->clearButton2->setEnabled(false);
}
//更新坐标系
void workdialog::UpdateChart(){
    if(this->tool_box->combobox_Change->currentIndex()==0){
        m_scatterSeries_B->clear();
        m_scatterSeries_T->clear();
        m_scatterSeries_B->append(this->SerialServer->GetPointSet().getPoint_B());
        m_scatterSeries_T->append(this->SerialServer->GetPointSet().getPoint_T());
    }
    if(this->tool_box->combobox_Change->currentIndex()==1){
        m_scatterSeries_B->clear();
        m_scatterSeries_T->clear();
        m_scatterSeries_B->append(this->SerialServer->GetPointSet().getPoint_B());
    }
    if(this->tool_box->combobox_Change->currentIndex()==2){
        m_scatterSeries_B->clear();
        m_scatterSeries_T->clear();
        m_scatterSeries_T->append(this->SerialServer->GetPointSet().getPoint_T());
    }
}
void workdialog::UpdateEditSlot(){
    this->tool_box->show_the_data->clear();
    UpdateShowEdit();
}
void workdialog::PointHoverdSlot(const QPointF &point, bool state){
    if(state){
        QString temp;
        temp+="("+QString::number(point.x())+","+QString::number(point.y())+")";
        m_ValueLabel->setText(temp);

        QPoint curPos=mapFromGlobal(QCursor::pos());
        m_ValueLabel->move(curPos.x() - m_ValueLabel->width()/2,curPos.y() - m_ValueLabel->height());

        m_ValueLabel->show();
    }
    else{
        m_ValueLabel->hide();
    }
}

workdialog::~workdialog()
{
    delete tool_box;
    delete m_ValueLabel;
    delete timers;
    delete readtimer;
    delete SerialServer;
}
