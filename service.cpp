#include "service.h"

Service::Service(std::string name, srv_I *srv_reff):name(name),req_rsp_data(srv_reff){
}

std::string Service::get_name(){
    return name;
}

srv_I *Service::get_srv(){
    return req_rsp_data;
}


Service::~Service(){
    delete req_rsp_data;
}
