import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    val kotlinVersion = "1.9.22"
    id("org.springframework.boot") version "3.2.2"
    id("io.spring.dependency-management") version "1.1.4"
    kotlin("jvm") version kotlinVersion
    kotlin("plugin.spring") version kotlinVersion
    kotlin("plugin.jpa") version kotlinVersion
}

group = "com.dclass"
version = "0.0.1-SNAPSHOT"

java {
    sourceCompatibility = JavaVersion.VERSION_17
}

repositories {
    mavenCentral()
    maven(url = "https://oss.sonatype.org/content/repositories/snapshots")
}

dependencies {
    implementation("org.springframework.boot:spring-boot-starter-data-jpa")
    implementation("org.springframework.boot:spring-boot-starter-web")
	implementation("org.springframework.boot:spring-boot-starter-validation")
    implementation("com.fasterxml.jackson.module:jackson-module-kotlin")
    implementation("org.springframework.boot:spring-boot-starter-thymeleaf")
    implementation("org.jetbrains.kotlin:kotlin-reflect")

    implementation("com.linecorp.kotlin-jdsl:jpql-dsl:3.3.1")
    implementation("com.linecorp.kotlin-jdsl:jpql-render:3.3.1")
    implementation("com.linecorp.kotlin-jdsl:spring-data-jpa-support:3.3.1")

    implementation("aws.sdk.kotlin:ses:1.0.30")
    implementation("aws.sdk.kotlin:s3:1.0.30")
    implementation("com.squareup.okhttp3:okhttp:5.0.0-alpha.11")
//    implementation("aws.smithy.kotlin:http-client-engine-okhttp:0.30.0")

    runtimeOnly("com.mysql:mysql-connector-j")

    testImplementation("org.springframework.boot:spring-boot-starter-test")
}

tasks.withType<KotlinCompile> {
    kotlinOptions {
        freeCompilerArgs += "-Xjsr305=strict"
        jvmTarget = "17"
    }
}

tasks.withType<Test> {
    useJUnitPlatform()
}

tasks {
    val copySecret by register<Copy>("copySecret") {
        from("./dclass-secret") // 서브모듈 디렉토리 경로
        include("application*.yml") // 복사할 파일들
        into("./src/main/resources") // 복사 위치
    }

    named("processResources") {
        dependsOn(copySecret)
    }
}