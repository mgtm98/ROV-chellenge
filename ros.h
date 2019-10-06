#ifndef ROS_H
#define ROS_H

#include <map>
#include <string>
#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>
#include <QTextCodec>
#include <rapidjson/document.h>
#include <functional>
#include "topic.h"
#include "msg.h"
#include "service.h"
#include "srv_.h"



class QRos : public QObject {
    Q_OBJECT
public:
    QRos(std::string,unsigned short);   
    void publish(Topic *);              
    void publish(Topic &);
    void subscrib(std::string, std::string, std::function<void(msg_I*)>);
    void send_request(Service *, std::function<void(srv_resp_I*)>);
private:
    QTcpSocket *socket;
    std::map<std::string, std::function<void(msg_I*)>> subscriber_table;
    std::map<std::string, std::function<void(srv_resp_I*)>> srv_response_table;
    std::string ip;
    int port;
    msg_I *creatMsg(rapidjson::Value::Object);
    srv_resp_I *creatResp(rapidjson::Value::Object);
    void send(std::string);

private slots:
    void handel_response();
};



#endif // ROS_H
