#include "ros.h"

QRos::QRos(std::string ip_arg, int port_arg){
    ip = ip_arg;
    port = port_arg;
    socket = new QTcpSocket();
//    connect(socket,SIGNAL(readyRead()),this,SLOT(handel_response()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(handel_response()));
//    connect(socket,SIGNAL(connected()),this,SLOT(handel_response()));
    socket->connectToHost(QHostAddress(QString::fromStdString(ip)), port_arg);
    connect( socket,SIGNAL(readyRead()),this,SLOT(handel_response()));
}

void QRos::publish(Topic t){
    std::string encodedData = "{'type' : 'topic', ";
    encodedData += "'name' : '" + t.get_name()+"',";
    encodedData += "'msg-type' : '" + t.get_msg()->get_Type()+"',";
    encodedData += "'msg' : " + t.get_msg()->encode()+" }\n";
    socket->write(encodedData.c_str());
    socket->waitForBytesWritten(100);
}

void QRos::subscrib(std::string topic_name){
    std::string request = "{'type' : 'topic_subscribe', 'name' : '"+topic_name+"'}";
    socket->write(request.c_str());
    socket->waitForBytesWritten(100);
}

void QRos::handel_response(){
    QByteArray data = socket->readAll();
    qDebug() << data;
}
