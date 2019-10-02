import time
from adafruit_servokit import ServoKit
from adafruit_motor import servo

class Camera:
	# def __init__(self,hat,name,channel,fallingValue):
	# 	self.hat = hat
	# 	self.name = name
	# 	self.channel = channel
	# 	self.fallingValue = fallingValue
	# 	self.hat.setPWM(channel,0,fallingValue)
	# 	self.servoPin = servoPin
	# 	GPIO.setmode(GPIO.BOARD)
	# 	GPIO.setup(self.servoPin, GPIO.OUT)
	# 	self.pwm = GPIO.PWM(self.servoPin, 50)
	# 	self.pwm.start(0)


	# def updatePWM(self,pwm):
	# 	self.fallingValue = pwm
	# 	self.hat.setPWM(self.channel,0,pwm)

	# kit = ServoKit(channels=16)
	def __init__(self, hat, channel_x, channel_y):
		# self.channel_x = channel_x
		# self.channel_y = channel_y
		self.servo_x = servo.Servo(hat.channels[channel_x])
		self.servo_y = servo.Servo(hat.channels[channel_y])


	def move(self, angle_x, angle_y):
		# duty = angle / 18 + 2
		# GPIO.output(self.servoPin, True)
		# self.pwm.ChangeDutyCycle(duty)
		# time.sleep(1)
		# GPIO.output(self.servoPin, False)
		# self.pwm.ChangeDutyCycle(0)

		# self.kit.servo[self.channel_x].angle = angle_x
		# self.kit.servo[self.channel_y].angle = angle_y

		self.servo_x.angle = angle_x
		self.servo_y.angle = angle_y

		
