from rov20.msg import camera_info
import rospy
from camera import Camera
from board import SCL, SDA
import busio
from adafruit_pca9685 import PCA9685


def control(data):
    global camera
    if data.action == "move":
        camera[data.index].move(data.x, data.y)
    elif data.action == "stream":
        camera[data.index].stream()
    elif data.action == "play":
        camera[data.index].play_stream()
    else:
        camera[data.index].stop_stream()
    return

if __name__ == "__main__":
    rospy.init_node("camera")
    rospy.Subscriber("cameraControl", camera_info, control)
    i2c_bus = busio.I2C(SCL, SDA)
    hat = PCA9685(i2c_bus)
    hat.frequency = 50

    host = "192.168.1.4"
    port1 = 5000
    port2 = 5001

    camera = []
    camera.append(Camera(hat, 6, 7, 0, host, port1))
    camera.append(Camera(hat, 8, 9, 1, host, port1))

    rospy.spin()
        
