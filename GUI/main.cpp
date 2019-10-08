#include "mainwindow.h"
#include <QApplication>
#include <QGst/Init>
int main(int argc, char *argv[])
{
    QRos *ros = new QRos("127.0.0.1",8006);

    QGst::init(&argc, &argv);
    QApplication a(argc, argv);
    MainWindow w(nullptr,ros);
    w.show();

    return a.exec();
}
