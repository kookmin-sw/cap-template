import dlib
import cv2
import numpy as np

predictor_file = './shape_predictor_68_face_landmarks.dat' 
image_file = './test/kimmingyu.jpeg' 

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor(predictor_file)

image = cv2.imread(image_file)
image_ycbcr = cv2.cvtColor(image, cv2.COLOR_BGR2YCrCb)

# https://www.researchgate.net/publication/262371199_Explicit_image_detection_using_YCbCr_space_color_model_as_skin_detection
# lower
lower = np.array([0, 133, 77], dtype=np.uint8)

# upper
upper = np.array([255, 173, 127], dtype=np.uint8)

skin_detect_mask = cv2.inRange(image_ycbcr, lower, upper)

# cv2.imshow("test", skin_detect_mask)


image_skin_detect = cv2.bitwise_and(image, image, mask=skin_detect_mask)

image_horizontal = np.hstack((image, image_skin_detect))

cv2.imshow("Face Landmark", image_horizontal)
key = cv2.waitKey(0)

if key == ord('q'):
    cv2.destroyAllWindows()