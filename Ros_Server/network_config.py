import json
import threading
from std_msgs.msg import String, Empty

msgTypes = {
    "std_msgs/Empty" : Empty,
    "std_msgs/String" : String,
}



s_obj = None

def generate_handeler(topic_name):
    return handlers_table[topic_name]

def Salary_Handeler(data):
    response = {
        "type" : "topic_response",
        "topic_name" : "Salary",
        "msg" : {
            "type" : "std_msgs/Empty",
        },
    }2

handlers_table = {
    "Salary" : Salary_Handeler,
}