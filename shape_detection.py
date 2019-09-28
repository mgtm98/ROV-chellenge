import cv2
import numpy as np

# the square is -1 because the image frame is counted a square
shapes={"square":-1,"circle":0,"line":0,"triangle":0}

image = cv2.imread("shapes.png")
gray =  cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
_,thresh=cv2.threshold(gray,250,255,0)

contours, _ = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
for c in contours:
    # Approximates a polygonal curve(s) with the specified precision.
    polygon = cv2.approxPolyDP(c, 0.01*cv2.arcLength(c,True),True)
    cv2.drawContours(image,[polygon],0,(0),5)

    if(len(polygon)==2):
        shapes["line"]+=1
        print("line")
    elif(len(polygon)==3):
        shapes["triangle"]+=1
        print("triangle")
    elif(len(polygon)==4):
        shapes["square"]+=1
        print("square")
    elif(len(polygon)>10):
        shapes["circle"]+=1
        print("circle")

cv2.imshow("image",image)
cv2.waitKey(0)