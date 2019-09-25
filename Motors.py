import time
import Adafruit_PCA9685

class Motor:
	def __init__(self,hat,name,channel,fallingValue):
		self.hat = hat
		self.name = name
		self.channel = channel
		self.fallingValue = fallingValue
		self.hat.setPWM(channel,0,fallingValue)


	def updatePWM(self,pwm):
		self.fallingValue = pwm
		self.hat.setPWM(self.channel,0,pwm)

	
