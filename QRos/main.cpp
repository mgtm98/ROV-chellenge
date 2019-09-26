#include <QCoreApplication>
#include "ros.h"
#include "msgs.h"
#include "msg_I.h"
#include "topic.h"
#include <QDebug>

void test(msg_I *msg){
    std_Empty *message =(std_Empty *) msg;
    qDebug() << "Empty Response";
}
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    QRos ros("127.0.0.1",8006);
    Topic t ("Salary", new std_Empty());
    ros.publish(t);
//    ros.subscrib("Salary", "std_msgs/Empty", *test);
//    ros.publish(t);
//    ros.publish(t);
//    ros.publish(t);
    qDebug() << "started";
    return a.exec();
}
