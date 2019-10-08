import time
import adafruit_pca9685
from board import SCL, SDA
import busio
import motion
from motor import *
from camera import *
from network import *
import rospy
from std_msgs.msg import String, Empty

# Code will be separated in diffrent nodes , there will not be a main node 
# Jimmy Changes .... please write comments to fully discribe why you do something or Y u added Something
# #constants
# iniFallingValue = 100

# #initialize hat
# i2c_bus = busio.I2C(SCL, SDA)
# hat = adafruit_pca9685.PCA9685(i2c_bus)
# # pwm = adafruit_pca9685.PWM(0x40)
# # pwm.setPWMFreq(50)
# hat.frequency = 50

# #initialize hardware devices
# frontLeftMotor = Motor(hat, 0, iniFallingValue)
# backlefttMotor = Motor(hat, 1, iniFallingValue)
# frontRightMotor = Motor(hat, 2, iniFallingValue)
# backRightMotor = Motor(hat, 3, iniFallingValue)

# verticalMotor1 = Motor(hat, 4, iniFallingValue)
# verticalMotor2 = Motor(hat, 5, iniFallingValue)  
# camera1 = Camera(hat, 6, 7)
# camera2 = Camera(hat, 8, 9)

# #Ros initialization
# if __name__ == "__main__":
# 	rospy.init_node("main")
# 	rospy.Subscriber("coordinates",Empty,getCoordinates)
# 	rospy.Subscriber("cameras",Empty,cameraMove)
# 	rospy.spin()

# def mapCoordinates(x, y):
#     # expected range -300 : 300
# 	stick_range = 300
# 	dead_zone = 50

# 	if abs(x) < dead_zone :
# 		x_pwm = 0
# 	else :
# 		x_pwm = (abs(x) - dead_zone) / (stick_range - dead_zone)

# 	if abs(y) < dead_zone :
# 		y_pwm = 0
# 	else :
# 		y_pwm = (abs(y) - dead_zone) / (stick_range - dead_zone)

# 	if x > 0 : right = 1
# 	else : right = 0

# 	if y > 0 : up = 1
# 	else : up = 0

# 	return x_pwm, y_pwm, right, up


# def getCoordinates(x, y):	
# 	#get x,y from qt	
# 	#controlX(x)
#     #controlY(y)
# 	if  x == 0 and y>0 :
# 		pwm = abs(y/320)
# 		upMovement(pwm)
# 	elif x ==0 and y<0 :
# 		 pwm = abs(y/320)
# 		 downMovement(pwm)
# 	elif y ==0 and x>0 :
# 		 pwm = abs(y/320)
# 		 rightMovement(pwm)
# 	elif y ==0 and x<0 :
# 		 pwm = abs(y/320)
# 		 leftMovement(pwm)
# 	elif  x<0:
# 		 pwm = abs(y/320)
# 		 leftMovement(pwm)
	
# 	#leftFrontPwm,leftBackPwm,rightFrontPwm,rightBackPwm = motion.mapCoordinates(x,y)
# 	#verticalPWM = motion.controlDepth(z)
# 	#leftFrontMotor.updatePWM(leftFrontPwm)
# 	#leftBackMotor.updatePWM(leftBackPwm)
# 	#rightFrontMotor.updatePWM(rightFrontPwm)
# 	#rightBackMotor.updatePWM(rightBackPwm)
# 	# verticalMotor1.updatePWM(verticalPWM)
# 	# verticalMotor2.updatePWM(verticalPWM)
# 	last_x = x
# 	last_y = y
# def cameraMove(data):	
# 	camera1.move()
# 	camera2.move()

# def upMovement(pwm):
# 	frontRightMotor.anticlockWise(pwm)
# 	frontLeftMotor.clockWise(pwm)
# 	backRightMotor.anticlockWise(pwm)
# 	backlefttMotor.clockWise(pwm)
# def downMovement(pwm):
# 	frontRightMotor.clockWise(pwm)
# 	frontLeftMotor.anticlockWise(pwm)
# 	backRightMotor.clockWise(pwm)
# 	backlefttMotor.anticlockWise(pwm)
# def leftMovement(pwm):
# 	frontRightMotor.anticlockWise(pwm)
# 	frontLeftMotor.anticlockWise(pwm)
# 	backRightMotor.clockWise(pwm)
# 	backlefttMotor.clockWise(pwm)
# def rightMovement(pwm):
# 	frontRightMotor.clockWise(pwm)
# 	frontLeftMotor.clockWise(pwm)
# 	backRightMotor.anticlockWise(pwm)
# 	backlefttMotor.anticlockWise(pwm)
# def clockMovement(pwm):
# 	frontRightMotor.clockWise(pwm)
# 	frontLeftMotor.clockWise(pwm)
# 	backRightMotor.clockWise(pwm)
# 	backlefttMotor.clockWise(pwm)
# def anticlockMovement(pwm):
# 	frontRightMotor.anticlockWise(pwm)
# 	frontLeftMotor.anticlockWise(pwm)
# 	backRightMotor.anticlockWise(pwm)
# 	backlefttMotor.anticlockWise(pwm)

