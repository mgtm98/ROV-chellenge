#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QRos *ros = new QRos("127.0.0.1",8006);

    QApplication a(argc, argv);
    MainWindow w(nullptr,ros);
    w.show();

    return a.exec();
}
