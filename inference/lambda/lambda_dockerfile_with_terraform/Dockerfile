FROM public.ecr.aws/lambda/python:3.12

COPY requirements.txt .
COPY lambda.py ${LAMBDA_TASK_ROOT}
COPY ./terraform ${LAMBDA_TASK_ROOT}

RUN pip3 install --no-cache-dir -r requirements.txt --target "${LAMBDA_TASK_ROOT}"
RUN chmod +x /var/task

CMD ["lambda.handler"]