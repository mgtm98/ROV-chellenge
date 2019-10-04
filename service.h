#ifndef SRV_H
#define SRV_H

#include <string>
#include "srv_.h"

class Service{
private:
    std::string name;
    srv_I *req_rsp_data;

public:
    Service(std::string,srv_I*);
    ~Service();
    std::string get_name();
    srv_I *get_srv();
    std::string get_srvType();
};

#endif // SRV_H
