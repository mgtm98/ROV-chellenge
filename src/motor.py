import time
import adafruit_pca9685

def map(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

class Motor:
	min_value = 1000
	max_value = 2000

	def __init__(self,hat,channel,initalValue):
		self.hat = hat
		self.channel = channel
		self.speed = initalValue
		# self.hat.setPWM(channel,0,initalValue)
		self.hat.channels[self.channel].duty_cycle = initalValue 
	
	def arm(self):
		self.updatePWM(0)
		time.sleep(1)
		self.updatePWM(max_value)
		time.sleep(1)
		self.updatePWM(min_value)
		time.sleep(0.5)
	
	def clockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		speed = map(speed, 0, 1, min_value, max_value)
		self.updatePWM(speed)
	
	def anticlockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		speed = map(speed, 0, 1, min_value, max_value)
		self.updatePWM(speed)

	def updatePWM(self,pwm):
		self.fallingValue = pwm
		# self.hat.setPWM(self.channel,0,pwm)
		self.hat.channels[self.channel].duty_cycle = pwm 

	
