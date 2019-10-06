#include "ros.h"

QRos::QRos(std::string ip_arg, unsigned short port_arg){
    ip = ip_arg;
    port = port_arg;
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress(QString::fromStdString(ip)), port_arg);
    connect(socket,SIGNAL(readyRead()),this,SLOT(handel_response()));
}

void QRos::publish(Topic *t){
    std::string encodedData = "{\"type\" : \"topic_publish\", ";
    encodedData += "\"topic_name\" : \"" + t->get_name()+"\",";
    encodedData += "\"msg-type\" : \"" + t->get_msg()->get_Type()+"\",";
    encodedData += "\"msg\" : " + t->get_msg()->encode()+" }";
    send(encodedData);
}

void QRos::publish(Topic &t){
    std::string encodedData = "{\"type\" : \"topic_publish\", ";
    encodedData += "\"topic_name\" : \"" + t.get_name()+"\",";
    encodedData += "\"msg-type\" : \"" + t.get_msg()->get_Type()+"\",";
    encodedData += "\"msg\" : " + t.get_msg()->encode()+" }";
    send(encodedData);
}


void QRos::subscrib(std::string topic_name, std::string msg_type, std::function<void(msg_I*)> handler){
    std::string request = "{\"type\" : \"topic_subscribe\", \"topic_name\" : \""+topic_name+"\", \"msg-type\" : \""+msg_type+"\"}";
    subscriber_table[topic_name]=handler;
    send(request);
}

void QRos::send_request(Service *srv, std::function<void(srv_resp_I*)> handler){
    std::string encodedData = "{\"type\" : \"service_request\", ";
    encodedData += "\"srv_name\" : \"" + srv->get_name()+"\",";
    encodedData += "\"data\" : " + srv->get_srv()->encode()+" }";
    srv_response_table[srv->get_name()] = handler;
    send(encodedData);
}

void QRos::handel_response(){
    QByteArray data = socket->readAll();
    QString data_str = QTextCodec::codecForMib(106)->toUnicode(data);
    qDebug().noquote() << data;
    rapidjson::Document json;
    json.Parse(data_str.toStdString().c_str());
    if(json["type"] == "topic_response"){
        rapidjson::Value::Object msgObject = json["msg"].GetObject();
        msg_I *msg = creatMsg(msgObject);
        std::string topicName = json["topic_name"].GetString();
        subscriber_table[topicName](msg);
    }else if(json["type"] == "srv-response"){
        rapidjson::Value::Object msgObject = json["response"].GetObject();
        srv_resp_I *rsp = creatResp(json.GetObject());
        srv_response_table[json["srv-name"].GetString()](rsp);
    }
}

void QRos::send(std::string data){
    socket->flush();
    socket->write(QByteArray(data.c_str()));
    socket->waitForBytesWritten(10);
    socket->flush();
}

// stuff to be modified here
msg_I *QRos::creatMsg(rapidjson::Value::Object msgObject){
    if(msgObject["type"] == "std_msgs/String"){
        std::string String = msgObject["data"].GetObject()["String"].GetString();
        std_String *s = new std_String(String);
        return s;
    }else if(msgObject["type"] == "std_msgs/Empty"){
        std_Empty *s = new std_Empty();
        return s;
    }else if(msgObject["type"] == "rov20/camera"){
        int index = msgObject["data"].GetObject()["index"].GetInt();
        std::string action = msgObject["data"].GetObject()["action"].GetString();
        int x = msgObject["data"].GetObject()["x"].GetInt();
        int y = msgObject["data"].GetObject()["y"].GetInt();
        camera_msg *s = new camera_msg(index,action,x,y);
        return s;
    }
}

srv_resp_I *QRos::creatResp(rapidjson::Value::Object msgObject){
     if(msgObject["srv-name"] == "test"){
         std::string output = msgObject["response"].GetObject()["output"].GetString();
         srv_resp_I *t = new test_srv_resp(output);
         return t;
     }
}
