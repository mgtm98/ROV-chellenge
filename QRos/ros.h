#ifndef ROS_H
#define ROS_H

#include <map>
#include <string>
#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>
#include <rapidjson/allocators.h>
#include "topic.h"
#include "msg_I.h"

class QRos : public QObject {
    Q_OBJECT
public:
     QRos(std::string,int);
     void publish(Topic);
     void subscrib(std::string);

private:
     QTcpSocket *socket;
     std::string ip;
     int port;

private slots:
    void handel_response();
};

#endif // ROS_H
