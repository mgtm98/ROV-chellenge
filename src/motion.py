#!/usr/bin/env python3
from rov20.msg import pln_motion, z_motion
from motor import Motor
import rospy
import Adafruit_PCA9685

def controlHandeler(pln_motionMsg):
    x_movement(pln_motionMsg.x_speed)
    y_movement(pln_motionMsg.y_speed)

def depthHandeler(z_motionMsg):
    print("code to control rov altitude with data given from depthControl node")

def x_movement(speed):
    frontRightMotor.clockWise(speed)
    frontLeftMotor.clockWise(speed)
    backRightMotor.anticlockWise(speed)
    backlefttMotor.anticlockWise(speed)

def y_movement(speed):
    frontRightMotor.anticlockWise(speed)
    frontLeftMotor.clockWise(speed)
    backRightMotor.anticlockWise(speed)
    backlefttMotor.clockWise(speed)

if __name__ == "__main__":
    rospy.init_node("motion")
    rospy.Subscriber("control", pln_motion, controlHandeler)
    rospy.Subscriber("depthControl", z_motion, depthHandeler)
    hat = Adafruit_PCA9685.PCA9685()               #initalizing Adafruit hat with default address 0x40
    hat.setPWMFreq(50)                             #setting pwm freq to 50 hz
    frontRightMotor = Motor(hat,0,0)
    backRightMotor = Motor(hat,1,0)
    frontLeftMotor = Motor(hat,2,0)
    backlefttMotor = Motor(hat,3,0)
    v1Motor = Motor(hat,4,50)
    v2Motor = Motor(hat,5,50)
    rospy.spin()
