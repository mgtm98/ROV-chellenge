#include "msgs.h"

std_String::std_String(std::string data):data(data){
}

std::string std_String::encode(){
    return "{\"String\" : \"" + data + "\"}";
}

std::string std_String::get_Type(){
    return "std_msgs/String";
}

std_Empty::std_Empty(){
}

std::string std_Empty::encode(){
    return "{\"Data\" : \"Empty\"}";
}

std::string std_Empty::get_Type(){
    return "std_msgs/Empty";
}


/*planner a (50,60);
ros.publish(a)

topicName,"planne",call

call(msg_I m){
    planner *a = (planner *)m;
}
*/
