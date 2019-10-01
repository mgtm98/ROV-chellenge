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
if __name__ == "__main__":
	rospy.init_node("main")
	rospy.Subscriber("coordinates",Empty,getCoordinates)
	rospy.Subscriber("cameras",Empty,cameraMove)
	rospy.spin()

def getCoordinates(data):
	#get x,y from qt	
	#controlX(x)
    #controlY(y)
	if  x ==0 and y>0 :
		pwm = abs(y/320)
		upMovement(pwm)
	elif x ==0 and y<0 :
		 pwm = abs(y/320)
		 downMovement(pwm)
	elif y ==0 and x>0 :
		 pwm = abs(y/320)
		 rightMovement(pwm)
	elif y ==0 and x<0 :
		 pwm = abs(y/320)
		 leftMovement(pwm)
	elif  x<0:
		 pwm = abs(y/320)
		 leftMovement(pwm)
	
	#leftFrontPwm,leftBackPwm,rightFrontPwm,rightBackPwm = motion.mapCoordinates(x,y)
	#verticalPWM = motion.controlDepth(z)
	#leftFrontMotor.updatePWM(leftFrontPwm)
	#leftBackMotor.updatePWM(leftBackPwm)
	#rightFrontMotor.updatePWM(rightFrontPwm)
	#rightBackMotor.updatePWM(rightBackPwm)
`	verticalMotor1.updatePWM(verticalPWM)
	verticalMotor2.updatePWM(verticalPWM)
	last_x = x
	last_y = y
def cameraMove(data):	
	camera1.move()
	camera2.move()

def upMovement(pwm):
		frontRightMotor.anticlockWise(pwm)
    	frontLeftMotor.clockWise(pwm)
   	 	backRightMotor.anticlockWise(pwm)
    	backlefttMotor.clockWise(pwm)
def downMovement(pwm):
		frontRightMotor.clockWise(pwm)
    	frontLeftMotor.anticlockWise(pwm)
    	backRightMotor.clockWise(pwm)
    	backlefttMotor.anticlockWise(pwm)
def leftMovement(pwm):
		frontRightMotor.anticlockWise(pwm)
    	frontLeftMotor.anticlockWise(pwm)
    	backRightMotor.clockWise(pwm)
    	backlefttMotor.clockWise(pwm)
def rightMovement(pwm):
		frontRightMotor.clockWise(pwm)
    	frontLeftMotor.clockWise(pwm)
    	backRightMotor.anticlockWise(pwm)
    	backlefttMotor.anticlockWise(pwm)
def clockMovement(pwm):
		frontRightMotor.clockWise(pwm)
    	frontLeftMotor.clockWise(pwm)
   	 	backRightMotor.clockWise(pwm)
    	backlefttMotor.clockWise(pwm)
def anticlockMovement(pwm):
		frontRightMotor.anticlockWise(pwm)
    	frontLeftMotor.anticlockWise(pwm)
   	 	backRightMotor.anticlockWise(pwm)
    	backlefttMotor.anticlockWise(pwm)

