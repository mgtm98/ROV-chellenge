import json
import threading
from std_msgs.msg import String, Empty
import time

msgTypes = {
    "std_msgs/Empty" : Empty,
    "std_msgs/String" : String,
}

topics = {}    
'''
    topic_Name : publisher obj
'''
subscribers = {}
'''
    topic_name : [[ports],T/F,msg_type]

'''

server_obj = None

def setServer(server):
    global server_obj
    server_obj = server

def get_handeler(topic_name):
    return handlers_table[topic_name]

def Salary_Handeler(data):
    response = {
        "type" : "topic_response",
        "topic_name" : "Salary",
        "msg" : {
            "type" : "std_msgs/Empty",
        },
    }
    for port in subscribers["Salary"][0]:
        server_obj.send_Data(port, str(json.dumps(response)))

def Time_Handeler(data):
    response = {
        "type" : "topic_response",
        "topic_name" : "Time",
        "msg" : {
            "type" : "std_msgs/String",
            "data" : {
                "String" : str(time.time())
            }
        },
    }
    for port in subscribers["Time"][0]:
        server_obj.send_Data(port, str(json.dumps(response)))

handlers_table = {
    "Salary" : Salary_Handeler,
    "Time" : Time_Handeler,
}