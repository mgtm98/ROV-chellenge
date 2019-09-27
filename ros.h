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
#include "topic.h"
#include "msg_I.h"
#include "msgs.h"

class QRos : public QObject {
    Q_OBJECT
public:
     QRos(std::string,unsigned short);
     void publish(Topic);
     void subscrib(std::string, std::string, void handler(msg_I*));

private:
     QTcpSocket *socket;
     std::map<std::string, void (*)(msg_I*)> subscriber_table;
     std::string ip;
     int port;
//     msg_I *creatMsg(rapidjson::Value::Object);

private slots:
    void handel_response();
};



#endif // ROS_H
