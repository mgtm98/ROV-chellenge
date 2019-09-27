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

class std_String : public msg_I{
//        type : std_msgs/String
//        data : String
public:
    std_String(std::string);
    std::string encode();
    std::string get_Type();
    std::string data;
};

class std_Empty: public msg_I{
//    type : std_msgs/Empty
public:
    std_Empty();
    std::string encode() ;
    std::string get_Type();
};






#endif // MSG_I_H
