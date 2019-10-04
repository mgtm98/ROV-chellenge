import time
from adafruit_servokit import ServoKit
from adafruit_motor import servo
import sys

import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject

class Camera:
	# kit = ServoKit(channels=16)
	def __init__(self, hat, channel_x, channel_y, location, host, port):
		# self.channel_x = channel_x
		# self.channel_y = channel_y
		self.host = host
		self.port = port
		self.location = "/dev/video" + str(location)
		self.servo_x = servo.Servo(hat.channels[channel_x])
		self.servo_y = servo.Servo(hat.channels[channel_y])


	def move(self, angle_x, angle_y):
		# self.kit.servo[self.channel_x].angle = angle_x
		# self.kit.servo[self.channel_y].angle = angle_y
		self.servo_x.angle = angle_x
		self.servo_y.angle = angle_y

	def stream(self):
		Gst.init(None)
		self.pipeline = Gst.Pipeline()
		
		src = Gst.ElementFactory.make("v412src")
		h264parse = Gst.ElementFactory.make("h264parse")
		rtph264pay = Gst.ElementFactory.make("rtph264pay")
		gdppay = Gst.ElementFactory.make("gdppay")

		src.set_property("device", self.location)
		rtph264pay.set_property("config-interval", "1")
		rtph264pay.set_property("pt", "96")

		sink = Gst.ElementFactory.make("udpsink")
		sink.set_property("host", self.host)
		sink.set_property("port", self.port)

		self.pipeline.add(src)
		self.pipeline.add(h264parse)
		self.pipeline.add(rtph264pay)
		self.pipeline.add(gdppay)
		self.pipeline.add(src)
		self.pipeline.add(sink)

		src.link(h264parse)
		h264parse.link(rtph264pay)
		rtph264pay.link(gdppay)
		gdppay.link(sink)
		
		bus = self.pipeline.get_bus() 
		bus.add_signal_watch()
		bus.connect("message", self.on_message, None)

		self.pipeline.set_state(Gst.State.PLAYING)

		loop = GObject.MainLoop()
		loop.run()

	def play_stream(self):
		self.pipeline.set_state(Gst.State.PLAYING)
	
	def stop_stream(self):
		self.pipeline.set_state(Gst.State.NULL)

	def on_message(self, bus, message):
		mtype = message.type
		
		if mtype == Gst.MessageType.EOS:
			print("End of stream")	
		elif mtype == Gst.MessageType.ERROR:
			err, debug = message.parse_error()
			print(err, debug)     
		elif mtype == Gst.MessageType.WARNING:
			err, debug = message.parse_warning()
			print(err, debug)             
		return True 