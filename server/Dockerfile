FROM bellsoft/liberica-openjdk-alpine:17

# Gradle 빌드 명령 실행
CMD ["./gradlew", "clean", "build"]

# 빌드된 JAR 파일 복사
ARG JAR_FILE=build/libs/*.jar
COPY ${JAR_FILE} app.jar

EXPOSE 8080

ENTRYPOINT ["java","-jar","/app.jar"]