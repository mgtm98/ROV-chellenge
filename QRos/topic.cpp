#include "topic.h"

Topic::Topic(std::string name, msg_I *msg_reff):name(name),msg(msg_reff){
}

std::string Topic::get_name(){
    return name;
}

msg_I *Topic::get_msg(){
    return msg;
}

std::string Topic::get_msgType(){
    return msg->get_Type();
}

Topic::~Topic(){
    delete msg;
}

