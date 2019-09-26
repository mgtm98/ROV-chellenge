import time
import adafruit_pca9685
import motion
import sensor
import motors
import camera
import network
#constants
iniFallingValue = 200

#initialize hat
hat = adafruit_pca9685.PCA9685()
pwm = PWM(0x40)
pwm.setPWMFreq(50)

#initialize hardware devices
leftFrontMotor = Motor(hat, 'LeftFrontMotor', 0, iniFallingValue)
leftBackMotor = Motor(hat, 'LeftBackMotor', 1, iniFallingValue)
rightFrontMotor = Motor(hat, 'RightFrontMotor', 2, iniFallingValue)
rightBackMotor = Motor(hat, 'RightBackMotor', 3, iniFallingValue)
camera1 = Camera(hat, 'Cam1', 4, iniFallingValue)
camera2 = Camera(hat, 'Cam2', 5, iniFallingValue)
while True:
	#get x,y,z,rotation from qt, pass them to mapCoordinates function and return pwms for each 		motor 
	leftFrontPwm,leftBackPwm,rightFrontPwm,rightBackPwm = motion.mapCoordinates()
	leftFrontMotor.updatePWM(leftFrontPwm)
	leftBackMotor.updatePWM(leftBackPwm)
	rightFrontMotor.updatePWM(rightFrontPwm)
	rightBackMotor.updatePWM(rightBackPwm)
	camera1.move()
	camera2,move()
