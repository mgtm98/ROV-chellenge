#ifndef MSGS_H
#define MSGS_H

#include "msg_I.h"
#include <string>

class std_String : public msg_I{
public:
    std_String(std::string);
    std::string encode() ;
    std::string get_Type();
private:
    std::string data;
};





#endif // MSGS_H
