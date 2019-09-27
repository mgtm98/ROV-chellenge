from PID import *
kp = 50
ki = 25
kd = 25
def mapCoordinates():

	#mapping from joystick to pwms

	return leftFrontPwm,leftBackPwm,rightFrontPwm,rightBackPwm



def controlDepth(z):
	depth = sensor.read()
	p  = PID(kp,ki,kd)
	output = p.update((z - depth))
	#if output >0 then pwm down
	#else pwm up

	return verticalPWM
