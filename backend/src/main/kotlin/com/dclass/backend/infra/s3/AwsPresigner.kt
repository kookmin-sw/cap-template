package com.dclass.backend.infra.s3

import aws.sdk.kotlin.runtime.auth.credentials.StaticCredentialsProvider
import aws.sdk.kotlin.services.s3.S3Client
import aws.sdk.kotlin.services.s3.model.GetObjectRequest
import aws.sdk.kotlin.services.s3.model.PutObjectRequest
import aws.sdk.kotlin.services.s3.presigners.presignGetObject
import aws.sdk.kotlin.services.s3.presigners.presignPutObject
import com.dclass.backend.infra.AwsProperties
import org.springframework.stereotype.Component
import kotlin.time.Duration.Companion.minutes

@Component
class AwsPresigner(
    private val properties: AwsProperties,
    private val s3Properties: AwsS3Properties
) {
    companion object {
        const val POST_IMAGE_FOLDER = "post-image"
    }

    private val client = S3Client {
        region = s3Properties.region
        credentialsProvider = StaticCredentialsProvider {
            accessKeyId = properties.accessKey
            secretAccessKey = properties.secretKey
        }
    }

    suspend fun getPostObjectPresigned(keyName: String): String {
        val unsignedRequest = GetObjectRequest {
            bucket = s3Properties.bucket
            key = "$POST_IMAGE_FOLDER/$keyName"
        }

        val presignedRequest = client.presignGetObject(unsignedRequest, 10.minutes)

        return presignedRequest.url.toString()
    }

    suspend fun putPostObjectPresigned(keyName: String): String {
        val unsignedRequest = PutObjectRequest {
            bucket = s3Properties.bucket
            key = "$POST_IMAGE_FOLDER/$keyName"
        }

        val presignedRequest = client.presignPutObject(unsignedRequest, 10.minutes)

        return presignedRequest.url.toString()
    }
}
