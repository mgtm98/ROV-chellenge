import json
import threading
from std_msgs.msg import String, Empty
from rov20.msg import pln_motion, raw_data, z_motion, camera
import time



topics = {} #don't change !!   
'''
    topic_Name : publisher obj
'''
subscribers = {} #don't change !!   
'''
    topic_name : [[ports],T/F,msg_type]
'''

server_obj = None #don't change !!   

def setServer(server):
    global server_obj
    server_obj = server

def get_subscribe_handeler(topic_name):
    return subscribe_handlers_table[topic_name]

def get_srv_handeler(srv_name):
    return services_handlers_table[srv_name]

# Stuff to add or modify
# def Salary_Handeler(data):
#     response = {
#         "type" : "topic_response",
#         "topic_name" : "Salary",
#         "msg" : {
#             "type" : "std_msgs/Empty",
#         },
#     }
#     for port in subscribers["Salary"][0]:
#         server_obj.send_Data(port, str(json.dumps(response)))

# def Time_Handeler(data):
#     response = {
#         "type" : "topic_response",
#         "topic_name" : "Time",
#         "msg" : {
#             "type" : "std_msgs/String",
#             "data" : {
#                 "String" : str(time.time())
#             }
#         },
#     }
#     for port in subscribers["Time"][0]:
#         server_obj.send_Data(port, str(json.dumps(response)))

# def Testsrv_Handeler(func,srvData):
#     output = func(srvData["data"]["input"]).output
#     return {
#         "output" : output
#         }

subscribe_handlers_table = {
    # "Salary" : Salary_Handeler,
    # "Time" : Time_Handeler,
}

services_handlers_table = {
    # "test" : Testsrv_Handeler,
}

msgTypes = {
    "std_msgs/Empty" : Empty,
    "std_msgs/String" : String,
    "rov20/pln_motion" : pln_motion,
    "rov20/raw_data" : raw_data,
    "rov20/z_motion" : z_motion,
    "rov20/camera"   : camera
}

srvTypes = {
    
}