import time
import adafruit_pca9685

def map(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

class Motor:
	# These values have to be calibrated
	min_cw = 0.7
	max_cw = 1

	center = 1.5

	min_ccw = 1.7
	max_ccw = 2

	def __init__(self,hat,channel,initalValue):
		self.hat = hat
		self.channel = channel
		self.speed = initalValue
		# self.hat.setPWM(channel,0,initalValue)
		self.hat.channels[self.channel].duty_cycle = initalValue 
	
	def arm(self):
		self.updatePWM(0)
		time.sleep(0.5)
		self.updatePWM(max_cw)
		time.sleep(0.5)
		self.updatePWM(min_cw)
		time.sleep(0.5)

# methode used to set the motor speed in equation of motion Jimmy
	def set_speed(self,speed):
		if speed < 0:
			self.anticlockWise(abs(speed))
		else :
			self.clockWise(speed)

	def calibrate(self):
		# to do
		pass
	
	def clockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		speed = map(speed, 0, 1, min_cw, max_cw)
		self.updatePWM(speed)
	
	def anticlockWise(self, speed):
		# from calibration of esc we will get the range of values to put
		speed = map(speed, 0, 1, min_ccw, max_ccw)
		self.updatePWM(speed)

	def stop(self):
		self.updatePWM(center)

	def updatePWM(self, pwm):
		self.fallingValue = pwm
		# self.hat.setPWM(self.channel,0,pwm)
		self.hat.channels[self.channel].duty_cycle = (pwm / 20) * 0xffff

	
