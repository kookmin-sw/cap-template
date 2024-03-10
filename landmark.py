import cv2
import dlib
import numpy as np
import matplotlib as plt
from sklearn.neighbors import KNeighborsClassifier
import pandas as pd

RIGHT_EYE = list(range(36, 42))
LEFT_EYE = list(range(42, 48))
MOUTH = list(range(48, 68))
NOSE = list(range(27, 36))
EYEBROWS = list(range(17, 27))
JAWLINE = list(range(1, 17))
ALL = list(range(0, 68))
EYES = list(range(36, 48))

predictor_file = './shape_predictor_68_face_landmarks.dat' 
image_file = './test/seulgi.jpeg' 

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(predictor_file)

image = cv2.imread(image_file)

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

rects = detector(gray, 1)
print("Number of faces detected: {}".format(len(rects)))

pos = []
for (i, rect) in enumerate(rects):
    points = np.matrix([[p.x, p.y] for p in predictor(gray, rect).parts()])
    show_parts = points[ALL]
    for (i, point) in enumerate(show_parts):
        x = point[0,0]
        y = point[0,1]
        pos.append([x,y])
        cv2.circle(image, (x, y), 1, (0, 255, 255), -1)
        cv2.putText(image, "{}".format(i + 1), (x, y - 2),
		cv2.FONT_HERSHEY_SIMPLEX, 0.3, (0, 255, 0), 1)
    
    result = []
    vertical = abs(pos[0][1] - pos[8][1])
    for i in range(16):
        cv2.line(image, (pos[i][0], pos[i][1]), (pos[i+1][0], pos[i+1][1]), (0, 255, 255))
    
    for i in range(8):
        result.append(abs(pos[i][0] - pos[16-i][0]) / vertical)
        cv2.line(image, (pos[i][0], pos[i][1]), (pos[16-i][0], pos[i][1]), (0, 255, 255))

    print(result)

cv2.imshow("Face Landmark", image)
key = cv2.waitKey(0)

if key == ord('q'):
    cv2.destroyAllWindows()
