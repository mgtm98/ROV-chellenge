#include "msgs.h"

std_String::std_String(std::string data):data(data){
}

std::string std_String::encode(){
    return "{\"String\" : \"" + data + "\"}";
}

std::string std_String::get_Type(){
    return "std_msgs/String";
}
