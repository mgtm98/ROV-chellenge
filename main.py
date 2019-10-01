import time
import adafruit_pca9685
import motion
from motors import *
from camera import *
from network import *
import rospy
from std_msgs.msg import String, Empty
#constants
iniFallingValue = 100

#initialize hat
hat = adafruit_pca9685.PCA9685()
pwm = PWM(0x40)
pwm.setPWMFreq(50)

#initialize hardware devices
leftFrontMotor = Motor(hat, 'LeftFrontMotor', 0, iniFallingValue)
leftBackMotor = Motor(hat, 'LeftBackMotor', 1, iniFallingValue)
rightFrontMotor = Motor(hat, 'RightFrontMotor', 2, iniFallingValue)
rightBackMotor = Motor(hat, 'RightBackMotor', 3, iniFallingValue)
verticalMotor1 = Motor(hat, 'VerticalMotor1', 4, iniFallingValue)
verticalMotor2 = Motor(hat, 'VerticalMotor2', 5, iniFallingValue)  
camera1 = Camera(hat, 'Cam1', 4, iniFallingValue)
camera2 = Camera(hat, 'Cam2', 5, iniFallingValue)

#Ros initialization
rospy.init_node("main")
rospy.Subscriber("coordinates",Empty,getCoordinates)
rospy.Subscriber("cameras",Empty,cameraMove)
rospy.spin()

def getCoordinates(data):	
	leftFrontPwm,leftBackPwm,rightFrontPwm,rightBackPwm = motion.mapCoordinates(x,y,angle)
	verticalPWM = motion.controlDepth(z)
	leftFrontMotor.updatePWM(leftFrontPwm)
	leftBackMotor.updatePWM(leftBackPwm)
	rightFrontMotor.updatePWM(rightFrontPwm)
	rightBackMotor.updatePWM(rightBackPwm)
`	verticalMotor1.updatePWM(verticalPWM)
	verticalMotor2.updatePWM(verticalPWM)

def cameraMove(data):	
	camera1.move()
	camera2.move()


