#ifndef MSGS_H
#define MSGS_H

#include "msg_I.h"
#include <string>

class std_String : public msg_I{
    /*
        type : std_msgs/String
        data : String
    */
public:
    std_String(std::string);
    std::string encode() ;
    std::string get_Type();
    std::string data;
};





#endif // MSGS_H
