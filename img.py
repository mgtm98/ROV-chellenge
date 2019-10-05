import cv2
import numpy as np
import argparse


# the square is -1 because the image frame is counted a square
shapes={"square":-1,"circle":0,"line":0,"triangle":0}
# example command: python shape_detection.py -i shapes.png -l 0 -t 1 -s 3 -c 1
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True, help="path to input image")
ap.add_argument("-l", "--line", required=True, help="number of lines")
ap.add_argument("-t", "--triangle", required=True, help="number of triangles")
ap.add_argument("-s", "--square", required=True, help="number of squares")
ap.add_argument("-c", "--circle", required=True, help="number of circles")
args = vars(ap.parse_args())

image = cv2.imread(args["image"])
gray =  cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
_,thresh=cv2.threshold(gray,250,255,0)

_,contours, _ = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)


for c in contours:
    # to eliminate noise
    if cv2.contourArea(c) < 1000:
        continue
    # Approximates a polygonal curve(s) with the specified precision.
    polygon = cv2.approxPolyDP(c, 0.01*cv2.arcLength(c,True),True)
    cv2.drawContours(image,[polygon],0,(0),5)

    if(len(polygon)==2):
        shapes["line"]+=1
    elif(len(polygon)==3):
        shapes["triangle"]+=1
    elif(len(polygon)==4):
        shapes["square"]+=1
    elif(len(polygon)>10):
        shapes["circle"]+=1
if(shapes["line"]==int(args["line"]) and shapes["triangle"]==int(args["triangle"]) 
        and shapes["square"]== int(args["square"]) and shapes["circle"] == int(args["circle"])):
    print("True")
else:
    print("False")

#cv2.imshow("image",image)
#cv2.waitKey(0)
