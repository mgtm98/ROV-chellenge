import time
import adafruit_pca9685

class Motor:
	def __init__(self,hat,channel,initalValue):
		self.hat = hat
		self.channel = channel
		self.speed = initalValue
		self.hat.setPWM(channel,0,initalValue)
		# self.hat.channels[self.channel].duty_cycle = pwm * 0xffff
		
	def clockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		self.updatePWM(speed)
	
	def anticlockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		self.updatePWM(speed)

	def updatePWM(self,pwm):
		self.fallingValue = pwm
		self.hat.setPWM(self.channel,0,pwm)
		# self.hat.channels[self.channel].duty_cycle = pwm * 0xffff

	
