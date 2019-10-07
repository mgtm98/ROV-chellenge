#!/usr/bin/env python3
from rov20.msg import pln_motion, z_motion
from motor import Motor, map
import rospy
from board import SCL, SDA
import busio
from adafruit_pca9685 import PCA9685
from PID import PID
from sensors import get_depth_temp

# removed x_movement and y_movement functions and implemented 
# the movement functionality in the callback function
def controlHandeler(pln_motionMsg):
    frontRightMotor.set_speed(pln_motionMsg.y_speed-pln_motion.x_speed)
    frontLeftMotor.set_speed(pln_motionMsg.y_speed+pln_motion.x_speed)
    backRightMotor.set_speed(-pln_motionMsg.y_speed-pln_motion.x_speed)
    backlefttMotor.set_speed(-pln_motionMsg.y_speed+pln_motion.x_speed)

def depthHandeler(z_motionMsg):
    # print("code to control rov altitude with data given from depthControl node")
    while True:
        target = z_motionMsg.z_speed
        max_value = 200
        current, _ = get_depth_temp()
        pwm = pid.update(target - current)
        if abs(pwm) > max_value : pwm = max_value
        pwm /= max_value
        v1Motor.set_speed(pwm)
        v2Motor.set_speed(pwm)
        if abs(target - current) > 0.01 :
            return True

if __name__ == "__main__":
    rospy.init_node("motion")
    rospy.Subscriber("control", pln_motion, controlHandeler)
    rospy.Subscriber("altitude", z_motion, depthHandeler)
    # hat = adafruit_pca9685.PCA9685()               #initalizing Adafruit hat with default address 0x40
    # hat.setPWMFreq(50)                             #setting pwm freq to 50 hz
    i2c_bus = busio.I2C(SCL, SDA)
    hat = PCA9685(i2c_bus)
    hat.frequency = 50

    kp = 20
    ki = 20
    kd = 20
    pid = PID(kp, ki, kd)

    frontRightMotor = Motor(hat,0,0)
    backRightMotor = Motor(hat,1,0)
    frontLeftMotor = Motor(hat,2,0)
    backlefttMotor = Motor(hat,3,0)
    v1Motor = Motor(hat,4,50)
    v2Motor = Motor(hat,5,50)
    rospy.spin()
