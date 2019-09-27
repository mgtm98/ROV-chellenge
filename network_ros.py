import rospy
import json
import threading
from network_config import get_handeler, msgTypes, topics, subscribers, setServer
from server import Server



def recive_Data(data):
    json_data = json.loads(data[0])
    if json_data["type"] == "topic_publish":
        publish(json_data)
    elif json_data["type"] == "topic_subscribe":
        subscribe(json_data,data[1])
    print("[JSON]   ",json_data)

def subscribe(data, port):
    if not(data["topic_name"] in subscribers):
        subscribers[data["topic_name"]] = [[],False,data["msg-type"]]
    if not(port in subscribers[data["topic_name"]]):
        subscribers[data["topic_name"]][0].append(port)
        update()

def client_dissconnected(port):
    print(subscribers)
    for k in subscribers:
        if port in subscribers[k][0]:
            subscribers[k][0].remove(port)

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
            subscribers[topic_name][1] = True
            args = {
                "topic_name" : topic_name,
                "msg-type" : subscribers[topic_name][2]
            }
            threading.Thread(target = threadHandel, args = [args]).start()

def threadHandel(args):
    rospy.Subscriber(args["topic_name"], msgTypes[args["msg-type"]], get_handeler(args["topic_name"]))
    rospy.spin()


rospy.init_node("Network")
s = Server("127.0.0.1",8008)
s.onRecive(recive_Data)
s.onDissconnect(client_dissconnected)
setServer(s)
s.start()
