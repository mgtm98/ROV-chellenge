import cv2
import numpy as np

img = cv2.imread("down_right.png")
hsv= cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
###################### THE MASK ##########################
lower_red = np.array([0,50,50])
upper_red = np.array([10,255,255])
mask0 = cv2.inRange(hsv, lower_red, upper_red)

lower_red = np.array([170,50,50])
upper_red = np.array([180,255,255])
mask1 = cv2.inRange(hsv, lower_red, upper_red)

mask = mask0+mask1

###################### THE DIRECTION #####################

direction = 1 # 0:up  1:right  2:down  3:left

contours, _ = cv2.findContours(mask,mode = cv2.RETR_EXTERNAL, method = cv2.CHAIN_APPROX_SIMPLE)
max_area = cv2.contourArea(contours[0])

red_contour=max(contours, key=cv2.contourArea)

print(max_area)
red_contour_area = cv2.minAreaRect(red_contour)
(line_x, line_y), (w, h), angel= red_contour_area

shape = img.shape
img_h = shape[0]
img_w = shape[1]

# print(x,y,w,h,img_h,img_w)

image = cv2.circle(img, (int(line_x), int(line_y)), 30, (255, 255, 255), 5)

extLeft = tuple(red_contour[red_contour[:, :, 0].argmin()][0])
extRight = tuple(red_contour[red_contour[:, :, 0].argmax()][0])
extTop = tuple(red_contour[red_contour[:, :, 1].argmin()][0])
extBot = tuple(red_contour[red_contour[:, :, 1].argmax()][0])

print(extLeft,extTop,extBot,extRight)

horizontal_error = img_w/10
vertical_error = img_h/10
center_x = img_w/2
center_y = img_h/2

if((direction == 0 or direction == 2) and (line_x < center_x -horizontal_error)):
    print("right")
elif((direction == 0 or direction == 2) and (line_x > center_x +horizontal_error)):
    print("left")
elif((direction == 1 or direction == 3) and (line_y < center_y - vertical_error)):
    print("up")
elif((direction == 1 or direction == 3) and (line_y > center_y + vertical_error)):
    print("down")
elif(extRight[0] > (img_w-img_w/10) and direction != 3):
    print("right")
elif(extLeft[0] < img_w/10 and direction != 1):
    print("left")
elif(extTop[1]<img_h/10 and direction !=2):
    print("up")
else:
    print("down")

##################### DRAWING #################

box = cv2.boxPoints(red_contour_area)
box = np.int0(box)
cv2.drawContours(img,[box],0,(0,255,0),3)


# cv2.imshow("1",img)
# # cv2.imshow("2",mask)
# cv2.waitKey(0)
