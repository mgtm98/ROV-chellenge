import rospy
import json
import threading
from network_config import generate_handeler
from server import Server

topics = {}
subscribers = {}

def recive_Data(data):
    json_data = json.loads(data[0])
    if json_data["type"] == "topic_publish":
        publish(json_data)
    elif json_data["type"] == "topic_subscribe":
        subscribe(json_data,data[1])
    print("[JSON]   ",json_data)

def subscribe(data, port):
    if not(data["topic_name"] in subscribers):
        subscribers[data["topic_name"]] = [[],False]
    if not(port in subscribers[data["topic_name"]]):
        subscribers[data["topic_name"]][0].append(port)
        update()


def publish(data):
    if(data["msg-type"] == "std_msgs/String"):
        if data["topic_name"] in topics:
            topics[data["topic_name"]].publish(data["msg"]["String"])
        else:
            topics[data["topic_name"]] = rospy.Publisher(data["topic_name"],msgTypes[data["msg-type"]],queue_size=5)
            topics[data["topic_name"]].publish(data["msg"]["String"])
        
    elif(data["msg-type"] == "std_msgs/Empty"):
        if data["topic_name"] in topics:
            topics[data["topic_name"]].publish()
            # print("already in topics")
        else:
            print("[INFO]    creating new topic",data["topic_name"])
            topics[data["topic_name"]] = rospy.Publisher(data["topic_name"],msgTypes[data["msg-type"]],queue_size=5)
            topics[data["topic_name"]].publish()
    print("[INFO]    Publishing in topic "+data["topic_name"])

def update():
    for topic_name in subscribers:
        if not subscribers[topic_name][1]:
            threading.Thread(target = threadHandel(topic_name), args = []).start()

def threadHandel(topic_name):
    return generate_handeler(topic_name)

rospy.init_node("Network")
s = Server("127.0.0.1",8006)
s.onRecive(recive_Data)
s.start()
