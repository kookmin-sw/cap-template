from utils import landmark, line, norm, ratio, vector
import cv2

def get_vector(img_path):

    display_img, pos = landmark.get_landmark(img_path)

    distances = line.get_line(display_img, pos)

    norm_distances = norm.get_norm(distances) #정규화 길이정보

    V = vector.get_vector(pos)

    A = vector.get_angles(V) #각도정보

    ratios = ratio.get_ratio(distances) #길이 간 비율 정보

    print("norm: ", norm_distances, "\n\n")
    print("angle: ", A, "\n\n")
    print("ratio: ", ratio, "\n\n")

    cv2.imshow("Face Landmark", display_img)
    cv2.waitKey(0)

img_path = './test/seulgi.jpeg'
get_vector(img_path)