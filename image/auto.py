import cv2
import numpy as np
#from matplotlib import pyplot as plt


DEBUG = False
video = cv2.VideoCapture('udpsrc port=8000 ! application/x-rtp,encoding-name=JPEG ! rtpjpegdepay ! jpegdec ! decodebin ! videoconvert ! appsink', cv2.CAP_GSTREAMER)
#while True:
#    r, frame = video.read()
#    print(frame)
#    print(r)
#    try:
#	
#        cv2.imwrite("test.jpg",frame)
#        cv2.imshow('yes', frame)
#        key = cv2.waitKey(1)
#        if key == 27:
#            break
#    except cv2.error as e:
#        print(e)

flag=True
direction = 0
prev_direction =0
# image = cv2.imread("red2.jpg")
###################### THE MASK ##########################
while True:
    ret, frame = video.read()
    if not ret:
        video = cv2.VideoCapture("grid.mp4")
        continue

    hsv= cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_red = np.array([0,50,50])
    upper_red = np.array([10,255,255])
    mask0 = cv2.inRange(hsv, lower_red, upper_red)

    lower_red = np.array([170,50,50])
    upper_red = np.array([180,255,255])
    mask1 = cv2.inRange(hsv, lower_red, upper_red)

    mask = mask0+mask1

    #############################CORRNERS########################

    corners = cv2.goodFeaturesToTrack(mask, 1, .99, 10)
    try:
        corners = np.int0(corners)
    except:
        continue

    for i in corners:
        corner_x, corner_y = i.ravel()
        cv2.circle(frame, (corner_x, corner_y), 3, [255, 255, 0], -1)

    # print("number of corners: ",len(corners))
    # cv2.imshow('Shi-Tomasi Corner Detector', mask)
    # if cv2.waitKey(0) & 0xff == 27:
    #     cv2.destroyAllWindows()

    #########################DIRECTIONS##################


    # image dimensions
    shape = frame.shape
    img_h = shape[0]
    img_w = shape[1]

    horizontal_error = img_w/10
    vertical_error = img_h/10
    center_x = img_w/2
    center_y = img_h/2

    #extreme points of the line
    contours, _ = cv2.findContours(mask,mode = cv2.RETR_EXTERNAL, method = cv2.CHAIN_APPROX_SIMPLE)
    red_contour=max(contours, key=cv2.contourArea)
    extLeft = tuple(red_contour[red_contour[:, :, 0].argmin()][0])
    extRight = tuple(red_contour[red_contour[:, :, 0].argmax()][0])
    extTop = tuple(red_contour[red_contour[:, :, 1].argmin()][0])
    extBot = tuple(red_contour[red_contour[:, :, 1].argmax()][0])

# to set the first direction
    if flag:
        flag=False
        if (extRight[0] > (img_w - horizontal_error)):
            direction = 1
            prev_direction=direction
            print("right")
        elif (extLeft[0] < horizontal_error):
            direction = 3
            prev_direction = direction
            print("left")
        elif (extTop[1] < vertical_error):
            direction = 0
            prev_direction = direction
            print("up")
        elif(extBot[1] > (img_h - vertical_error)):
            direction = 2
            prev_direction = direction
            print("down")
        continue

########### searching for the circle ################
  #  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
   # stop = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1.6, 50)
    #if(stop is not None):
     #   print("STOP!!")
      #  break
    # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # _, thresh = cv2.threshold(gray, 180, 255, 0)
    #
    # contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    # coins = 0
    # finished = False
    # for c in contours:
    #     # to eliminate noise
    #     if cv2.contourArea(c) < 1000:
    #         continue
    #     # Approximates a polygonal curve(s) with the specified precision.
    #     polygon = cv2.approxPolyDP(c, 0.005 * cv2.arcLength(c, True), True)
    #     cv2.drawContours(frame, [polygon], 0, (0), 5)
    #
    #     if (len(polygon) > 50):
    #         print(len(polygon))
    #         print("STOP!!")
    #         finished = True
    # if finished:
    #     break
#################################################
    '''if direction == 0:
        print("Y: ", extTop[1] - center_y)
    elif direction == 2:
        print("Y: ", extBot[1] - center_y)
    elif direction == 1:
        print("X: ", extRight[0] - center_x)
    elif direction == 3:
        print("X: ", extLeft[0] - center_x)'''

    if(center_x - horizontal_error/2 < corner_x < center_x + horizontal_error/2
            and center_y - vertical_error/2 < corner_y < center_y + vertical_error/2 ):
        if (extRight[0] > (img_w - horizontal_error) and direction != 3):
            # print(direction)
            # print("prev: ", prev_direction)

            if prev_direction == 3 or direction == 1:
                continue
            prev_direction=direction
            direction = 1
            print("right")
        elif (extLeft[0] < horizontal_error and direction != 1):
            # print(direction)
            # print("prev: ",prev_direction)

            if prev_direction == 1 or direction == 3:
                continue
            prev_direction=direction
            direction = 3
            print("left")
        elif (extTop[1] < vertical_error and direction != 2):
            # print(direction)
            # print("prev: ", prev_direction)

            if prev_direction == 2 or direction == 0:
                continue
            prev_direction=direction
            direction = 0
            print("up")
        elif(extBot[1] > (img_h - vertical_error) and direction != 0):
            # print(direction)
            # print("prev: ", prev_direction)

            if prev_direction == 0 or direction == 2:
                continue
            prev_direction=direction
            direction = 2
            print("down")
    if (extBot[1] > (img_h - vertical_error/2) and extTop[1] < vertical_error/2):
        # print("IT HAS ENTERED", prev_direction)
        if(direction == 0 or direction == 2):
            prev_direction = direction
    elif(extLeft[0] < horizontal_error/2  and extRight[0] > (img_w - horizontal_error/2) ):
        # print("IT HAS ENTERED", prev_direction)
        if(direction==1 or direction ==3):
            prev_direction = direction

    cv2.imshow("frame", frame)
    # cv2.imshow("mask",mask)
    key = cv2.waitKey(1)
    if key == 27:
        break

















    # if DEBUG:
    #     contours, _ = cv2.findContours(mask,mode = cv2.RETR_EXTERNAL, method = cv2.CHAIN_APPROX_SIMPLE)
    #     red_contour=max(contours, key=cv2.contourArea)
    #     red_contour_area = cv2.minAreaRect(red_contour)
    #     (line_x, line_y), (w, h), angel= red_contour_area
    #     cv2.drawContours(image,[red_contour],0,(0),5)
    #     cv2.circle(image, (int(line_x),int(line_y)), 5, (0,0,0), thickness=3)

    # cv2.imshow("1",mask)
    # cv2.imshow("2",mask)
    # cv2.waitKey(0)
video.release()
cv2.destroyAllWindows()
