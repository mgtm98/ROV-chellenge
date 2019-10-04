#ifndef TOPIC_H
#define TOPIC_H

#include "msg.h"
#include <string.h>

class Topic{
private:
    std::string name;
    msg_I *msg;

public:
    Topic(std::string,msg_I*);
    ~Topic();
    std::string get_name();
    msg_I *get_msg();
    std::string get_msgType();
};

#endif // TOPIC_H
