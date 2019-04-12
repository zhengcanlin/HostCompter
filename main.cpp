#include "workdialog.h"
#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QMainWindow window;
    workdialog *w=new workdialog;
    w->setWindowTitle("zhu");
    w->show();
    //window.setCentralWidget(w);
    //window.show();

    return a.exec();
}
