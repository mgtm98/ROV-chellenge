#!/usr/bin/env python3

import rospy
import json
import threading
from network_config import *
from server import Server



def recive_Data(data):
    print(data)
    json_data = json.loads(data[0])
    if json_data["type"] == "topic_publish":
        publish(json_data)
    elif json_data["type"] == "topic_subscribe":
        subscribe(json_data,data[1])
    elif json_data["type"] == "service_request":
        srv_req(json_data,data[1])
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
            threading.Thread(target = subscibe_threadHandel, args = [args]).start()

def subscibe_threadHandel(args):
    rospy.Subscriber(args["topic_name"], msgTypes[args["msg-type"]], get_subscribe_handeler(args["topic_name"]))
    rospy.spin()

def srv_req(data, port):
    args = {
        "port" : port,
        "srv_req" : data
    }
    threading.Thread(target = srvReq_threadHandel, args = [args]).start()

def srvReq_threadHandel(args):
    try:
        rospy.wait_for_service(args["srv_req"]["srv_name"])
        try:
            func = rospy.ServiceProxy(args["srv_req"]["srv_name"],srvTypes[args["srv_req"]["srv_name"]])
            out = get_srv_handeler(args["srv_req"]["srv_name"])(func,args["srv_req"])
            resp = {
                "type" : "srv-response",
                "srv-name" : args["srv_req"]["srv_name"],
                "response" : out  
            }
        except Exception as e :
            resp = {
                "type" : "srv-Error #1",
                "srv-name" : args["srv_req"]["srv_name"],
                "response" : {
                    "msg" : "out happened in request srv",
                    "Exception" : str(e)
                }
            }
    except :
        resp = {
                "type" : "srv-Error #2",
                "srv-name" : args["srv_req"]["srv_name"],
                "response" : {
                    "msg" : "srv is not available"
                }
            }
    s.send_Data(args["port"],str(json.dumps(resp)))


rospy.init_node("Network")
s = Server("127.0.0.1",8009)
s.onRecive(recive_Data)
s.onDissconnect(client_dissconnected)
setServer(s)
s.start()
