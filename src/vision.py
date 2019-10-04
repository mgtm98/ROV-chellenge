#!/usr/bin/env python3

import rospy

from rov20.msg import camera_info
from camera import Camera

def callback (data):
    print(data.index)
    print(data.action)
    print(data.x)
    print(data.y)

if __name__ == "__main__":
    rospy.Subscriber("camera",camera_info,callback)    