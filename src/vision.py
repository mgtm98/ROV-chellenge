from rov20.msg import camera_info
from rov20.srv import lights
import rospy
from camera import Camera
from board import SCL, SDA
import busio
from adafruit_pca9685 import PCA9685


def control(data):
    global camera
    if data.action == "move":
        camera[data.index].move(data.x, data.y)
    elif data.action == "start":
        camera[data.index].start_stream()
    elif data.action == "play":
        camera[data.index].play()
    elif data.action == "pause":
        camera[data.index].pause()
    else:
        camera[data.index].stop()
    return

def lights_handeler(data):
    if(data.command == "on"):
        print("turining lights on")
    else :
        print("turning lights off")
    return "OK"

if __name__ == "__main__":
    rospy.init_node("vision")
    rospy.Subscriber("camera", camera_info, control)    #topic name is camera not cameraControl
    i2c_bus = busio.I2C(SCL, SDA)
    hat = PCA9685(i2c_bus)
    hat.frequency = 50

    host = "192.168.1.4"
    port1 = 5000
    port2 = 5001

    camera = []
    camera.append(Camera(hat, 6, 7, 0, host, port1))
    camera.append(Camera(hat, 8, 9, 1, host, port1))

    lightsSrv = rospy.Service("lights",lights,lights_handeler)
    rospy.spin()
        
