#include <QCoreApplication>
#include "ros.h"
#include "msgs.h"
#include "msg_I.h"
#include "topic.h"
#include <QDebug>

void test(msg_I *msg){
    std_String *message =(std_String *) msg;
    qDebug() << QString::fromStdString(message->data);
}
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    QRos ros("127.0.0.1",8005);
    Topic t ("test", new std_String("test string"));
//    ros.publish(t);
    ros.subscrib("test",*test);
    qDebug() << "started";
    return a.exec();
}
