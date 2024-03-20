FROM public.ecr.aws/lambda/python:3.10 as lambda-image

# 사용할 환경 : 우분투
FROM ubuntu:latest

# 작업 디렉토리 설정
RUN mkdir /var/task
WORKDIR /var/task

# labmda 런타임 이미지 복사
COPY lambda.py /var/task/
COPY test /tmp
COPY --from=lambda-image /var/runtime /var/runtime

# python 및 빌드 종속성 설치
RUN apt update && apt install -y libgl1-mesa-glx libglib2.0-0
RUN apt install python3 -y --no-install-recommends
RUN apt install python3-pip -y --no-install-recommends

RUN pip3 install awslambdaric
RUN pip3 install boto3

# 선택 packages 설치
RUN apt install lame -y
RUN pip install requests midi2audio 

# Lambda Runtime Interface Emulator를 추가하고 보다 간단한 로컬 실행을 위해 ENTRYPOINT에서 스크립트 사용
COPY ./entry_script.sh /entry_script.sh
ADD aws-lambda-rie /usr/local/bin/aws-lambda-rie

RUN chmod 755 /entry_script.sh
RUN chmod 755 /usr/local/bin/aws-lambda-rie

RUN apt update && apt install -y wget gnupg lsb-release coreutils
RUN wget -O- https://apt.releases.hashicorp.com/gpg | gpg --dearmor | tee /usr/share/keyrings/hashicorp-archive-keyring.gpg
RUN echo "deb [signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] https://apt.releases.hashicorp.com $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/hashicorp.list
RUN apt update && apt install -y terraform

ENTRYPOINT [ "/entry_script.sh" ]

CMD [ "lambda.handler" ]
