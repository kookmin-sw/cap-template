import subprocess
import boto3

def handler(event, context):
    # 작업 디렉토리를 /tmp로 설정
    working_dir = "/tmp"
    
    # Terraform 초기화 (작업 디렉토리: /tmp)
    subprocess.run(["terraform", "init", "-input=false"], cwd=working_dir)
    
    # Terraform 적용 (작업 디렉토리: /tmp)
    subprocess.run(["terraform", "apply", "-auto-approve"], cwd=working_dir)
    
    # Terraform 파괴 (작업 디렉토리: /tmp)
    # 오타 수정: '-auto--approve' -> '-auto-approve'
    subprocess.run(["terraform", "destroy", "-auto-approve"], cwd=working_dir)

    return {
        'statusCode': 200,
        'body': 'Terraform Applied and Destroyed Successfully in /tmp directory'
    }
