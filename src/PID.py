import time

class PID:

  def __init__(self,kp,ki,kd):
	self.kp = kp
	self.ki = ki
	self.kd = kd
	
	self.sample_time = 0.09
	self.current_time = time.time()
	self.last_time = self.current_time
	self.clear()

  def clear(self):
	self.Pterm = 0.0
	self.Iterm = 0.0
	self.Dterm = 0.0
	self.last_error =0.0
	self.wind_up = 20.0
	self.int_error= 0.0
	self.output = 0.0
	
  def update(self,error):
	self.error = error
	self.current_time = time.time()
	delta_time = self.current_time - self.last_time
	delta_error = self.error - self.last_error
	if(delta_time >= self.sample_time):
		self.Pterm = self.kp * self.error
		self.Item += delta_error * delta_time
		
		if(self.Iterm >= self.wind_up):
			self.iterm = self.wind_up
		elif(self.Iterm < self.wind_up):
			self.Iterm = -self.wind_up

		self.Dterm = delta_error/delta_time
		
		self.last_time = self.current_time
		self.last_error = self.error
		self.output = self.Pterm + (self.ki * self.Iterm) + (self.Dterm * self.kd)
 		
	return self.output



	
