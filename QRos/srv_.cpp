#include "srv_.h"

test_srv::test_srv(std::string req):req(req){
}

std::string test_srv::encode(){
    return "{\"input\" : \"" + req + "\"}";
}

test_srv_resp::test_srv_resp(std::string out):output(out){
}

