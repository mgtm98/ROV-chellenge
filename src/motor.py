import time
import Adafruit_PCA9685

class Motor:
    def __init__(self,hat,channel,initalValue):
        self.hat = hat
        self.channel = channel
        self.speed = initalValue
        self.hat.setPWM(channel,0,initalValue)

	def clockWise(self,speed):
		# from calibration of esc we will get the range of values to put
		updatePWM(speed)
	
	def anticlockWise(self,speed):
		# from calibration of esc we will get the range of values to put
		updatePWM(speed)

	def updatePWM(self,pwm):
		self.fallingValue = pwm
		self.hat.setPWM(self.channel,0,pwm)

	
