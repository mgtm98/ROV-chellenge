#ifndef MSG_I_H
#define MSG_I_H

#include <string>
class msg_I{
public:
    virtual std::string encode(){
        return "";
    }
    virtual std::string get_Type(){
        return "hhh";
    }
    virtual ~msg_I(){}
};




#endif // MSG_I_H
