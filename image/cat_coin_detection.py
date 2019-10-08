import cv2
import numpy as np

image = cv2.imread("yarab.png")

###############COINS#########################
blurred_image = cv2.GaussianBlur(image,(15,15),cv2.BORDER_DEFAULT)
coins_gray = cv2.cvtColor(blurred_image, cv2.COLOR_BGR2GRAY)

output = image.copy()
cv2.imshow("output1", coins_gray)
cv2.waitKey(0)

coins = cv2.HoughCircles(coins_gray, cv2.HOUGH_GRADIENT, 1.2, 50)
if coins is not None:
    # convert the (x, y) coordinates and radius of the circles to integers
    coins = np.round(coins[0, :]).astype("int")
    print("number of coins:",len(coins))

    # loop over the (x, y) coordinates and radius of the circles
    for (x, y, r) in coins:
        # draw the circle in the output image, then draw a rectangle
        # corresponding to the center of the circle
        cv2.circle(output, (x, y), r, (0, 255, 0), 4)
        cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

    # show the output image
    cv2.imshow("output", np.hstack([image, output]))
    cv2.waitKey(0)

############################CATS############################

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


detector = cv2.CascadeClassifier("haarcascade_frontalcatface.xml")
rects = detector.detectMultiScale(gray, scaleFactor=1.1,minNeighbors=5, minSize=(20, 20))

print("number of coins with cats:",len(rects))

for (i, (x, y, w, h)) in enumerate(rects):
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)
    cv2.putText(image, "Cat #{}".format(i + 1), (x, y - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 0, 255), 2)

cv2.imshow("Cat Faces", image)
cv2.waitKey(0)