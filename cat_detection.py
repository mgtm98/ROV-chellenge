# import the necessary packages
import argparse
import cv2


image = cv2.imread("cats.jpg")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


detector = cv2.CascadeClassifier("haarcascade_frontalcatface.xml")
rects = detector.detectMultiScale(gray, scaleFactor=1.1,minNeighbors=5, minSize=(20, 20))

print(len(rects))

for (i, (x, y, w, h)) in enumerate(rects):
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 0, 255), 2)
    cv2.putText(image, "Cat #{}".format(i + 1), (x, y - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 0, 255), 2)

cv2.imshow("Cat Faces", image)
cv2.waitKey(0)