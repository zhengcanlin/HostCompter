#ifndef DIALOG_H
#define DIALOG_H

#include "pointset.h"
#include "serialport.h"

#include <QDialog>
#include <QWidget>
#include <QDebug>
#include <QTimer>

#include <QtCharts/QChart>
#include <QtCharts/QScatterSeries>
#include <QChartView>
#include <QValueAxis>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLineEdit>

#include <QPointF>
#include <QList>
using namespace QtCharts;
class workdialog : public QWidget
{
    Q_OBJECT

public:
    workdialog(QWidget *parent = 0);
    ~workdialog();
    void initChart();
    void InitLayout();
    void InitCombobox();
    void InitButton();
    void UpdateShowEdit();
public slots:
    void OpenPort();                //打开串口，并且开始每500ms从串口对象读取点集更新画布
    void ClosePort();               //关闭串口和定时器
    void UpdatePortCom();           //更新串口combobox
    void UpdateChart();             //更新画布

    void UpdateEditSlot();

    void PointHoverdSlot(const QPointF &point,bool state);
private:
    struct control_s;
    control_s *tool_box;
    QChart* m_chart;
    QScatterSeries* m_scatterSeries_B;
    QScatterSeries* m_scatterSeries_T;
    QValueAxis* m_axisX;
    QValueAxis* m_axisY;
    QChartView* m_chartView;
    QLabel *m_ValueLabel;

    QTimer *timers;
    QTimer *readtimer;
    SerialPort *SerialServer;
};

#endif // DIALOG_H
