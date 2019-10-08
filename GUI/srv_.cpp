#include "srv_.h"

test_srv::test_srv(std::string req):req(req){
}

std::string test_srv::encode(){
    return "{\"input\" : \"" + req + "\"}";
}

test_srv_resp::test_srv_resp(std::string out):output(out){
}

lights_srv::lights_srv(std::string command):command(command){
}

std::string lights_srv::encode(){
    return "{\"command\" : \"" + command + "\"}";
}

lights_srv_resp::lights_srv_resp(std::string resp):response(resp){
}

