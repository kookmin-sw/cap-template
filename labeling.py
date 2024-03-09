import cv2
import dlib
import numpy as np

#랜드마크 번호에 따른 부위
RIGHT_EYE = list(range(36, 42))
LEFT_EYE = list(range(42, 48))
MOUTH = list(range(48, 68))
NOSE = list(range(27, 36))
EYEBROWS = list(range(17, 27))
JAWLINE = list(range(1, 17))
ALL = list(range(0, 81))
EYES = list(range(36, 48))
FOREHEAD = list(range(68, 81))

predictor_file = './shape_predictor_81_face_landmarks.dat' 
image_file = './test/seulgi.jpeg' 

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(predictor_file)

image = cv2.imread(image_file)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
display_image = image

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
        cv2.circle(display_image, (x, y), 1, (0, 255, 255), -1)
        cv2.putText(display_image, "{}".format(i + 1), (x, y - 2),
		cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 0), 1)
    
    result = []
    vertical = abs(pos[0][1] - pos[8][1])

    D_LIST = [(2,14),(76,79),(71,8),(8, 12),(4,12),(6,10),(7,9)] #선분을 만들 주요 점 관계
    for i in range(7):
        start, end = D_LIST[i]
        print("start", start, "end", end)
        cv2.line(display_image, (pos[start][0], pos[start][1]), (pos[end][0], pos[end][1]), (0, 0, 255))
        cv2.putText(display_image, "D{}".format(i + 1), (pos[start][0], pos[start][1] - 2), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 0, 255), 1)
    
    # for i in range(8):
    #     result.append(abs(pos[i][0] - pos[16-i][0]) / vertical)
    #     cv2.line(gray, (pos[i][0], pos[i][1]), (pos[16-i][0], pos[i][1]), (0, 255, 255))

    print(result)


cv2.imshow("Face Landmark", display_image)
cv2.waitKey(0)