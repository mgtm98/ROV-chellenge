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
//        data : {String
//               }
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

class pln_motion: public msg_I{
//    type : rov20/pln_motion
public:

    pln_motion(double,double);
    std::string encode() ;
    std::string get_Type();
    double x_speed;
    double y_speed;

};

class z_motion: public msg_I{
//    type : rov20/z_motion
public:

    z_motion(double);
    std::string encode() ;
    std::string get_Type();
    double z_speed;


};

class raw_data: public msg_I{
//    type : rov20/row_data
public:
    raw_data(int,int,int);
    std::string encode() ;
    std::string get_Type();
    int x_speed;
    int y_speed;
    int z_speed;
};


class camera_msg: public msg_I{
//    type : rov20/row_data
public:
    camera_msg(int,std::string,int,int);
    std::string encode() ;
    std::string get_Type();
    int index;
    int x;
    int y;
    std::string action;
};







#endif // MSG_I_H
