#include "workdialog.h"
#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    workdialog *w=new workdialog;
    w->setWindowTitle("HostComputer");
    w->show();
    return a.exec();
}
