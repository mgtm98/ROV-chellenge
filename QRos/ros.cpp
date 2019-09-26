#include "ros.h"

QRos::QRos(std::string ip_arg, unsigned short port_arg){
    ip = ip_arg;
    port = port_arg;
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress(QString::fromStdString(ip)), port_arg);

    connect(socket,SIGNAL(readyRead()),this,SLOT(handel_response()));
}

void QRos::publish(Topic t){
    std::string encodedData = "{\"type\" : \"topic\", ";
    encodedData += "\"name\" : \"" + t.get_name()+"\",";
    encodedData += "\"msg-type\" : \"" + t.get_msg()->get_Type()+"\",";
    encodedData += "\"msg\" : " + t.get_msg()->encode()+" }";
    socket->write(encodedData.c_str());
    socket->waitForBytesWritten(100);
}

void QRos::subscrib(std::string topic_name, void (*handler)(msg_I*)){
    std::string request = "{\"type\" : \"topic_subscribe\", \"name\" : \""+topic_name+"\"}";
    subscriber_table[topic_name]=handler;
    socket->write(request.c_str());
    socket->waitForBytesWritten(100);
}

void QRos::handel_response(){
    QByteArray data = socket->readAll();
    QString data_str = QTextCodec::codecForMib(106)->toUnicode(data);
//    qDebug().noquote() << data;
    rapidjson::Document json;
    json.Parse(data_str.toStdString().c_str());
    if(json["type"] == "topic_response"){
        qDebug().noquote() << "here";
        rapidjson::Value::Object msgObject = json["msg"].GetObject();
        msg_I *msg = creatMsg(msgObject);
        std::string topicName = json["topic_name"].GetString();
        (*subscriber_table[topicName])(msg);
    }
}

msg_I *QRos::creatMsg(rapidjson::Value::Object msgObject){
    if(msgObject["type"] == "std_msgs/String"){
        std::string String = msgObject["data"].GetObject()["String"].GetString();
        std_String *s = new std_String(String);
        return s;
    }
}
