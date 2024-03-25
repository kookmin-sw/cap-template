import cv2
import os


def fullbody_detect(person_dir):
    cascade_path = "./haarcascade_fullbody.xml"
    # 폴더 내의 모든 파일에 대해 반복
    for filename in os.listdir(person_dir):
        file_path = os.path.join(person_dir, filename)

        # fullbody classifier 생성
        fullbody_cascade = cv2.CascadeClassifier(cascade_path)

        img = cv2.imread(file_path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # fullbody 검출
        fullbodies = fullbody_cascade.detectMultiScale(gray, scaleFactor=1.1)

        # fullbody 검출이 안 된 경우 파일 삭제
        if len(fullbodies) == 0:
            os.remove(file_path)
            print(f"Deleted image: {filename}")
