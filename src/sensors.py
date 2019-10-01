#!/usr/bin/env python3
from rov20.msg import raw_data
import rospy

if __name__ == "__main__":
    rospy.init_node("sensors")
    sensorPublisher = rospy.Publisher("Sensore_Reading",raw_data,queue_size=5)
        