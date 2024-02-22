package com.dclass.backend.infra.mail

import aws.sdk.kotlin.runtime.auth.credentials.StaticCredentialsProvider
import aws.sdk.kotlin.services.ses.SesClient
import aws.sdk.kotlin.services.ses.model.*
import com.dclass.backend.application.mail.MailSender
import com.dclass.backend.infra.AwsProperties
import org.springframework.stereotype.Component

@Component
class AwsMailSender(
    private val awsProperties: AwsProperties
) : MailSender {

    private val client: SesClient = SesClient {
        region = "ap-northeast-2"
        credentialsProvider = StaticCredentialsProvider {
            accessKeyId = awsProperties.accessKey
            secretAccessKey = awsProperties.secretKey
        }
    }

    override suspend fun send(toAddress: String, subjectVal: String, bodyHtml: String) {
        val destinationOb = Destination {
            toAddresses = listOf(toAddress)
        }

        val contentOb = Content {
            data = bodyHtml
        }

        val subOb = Content {
            data = subjectVal
        }

        val bodyOb = Body {
            html = contentOb
        }

        val msgOb = Message {
            subject = subOb
            body = bodyOb
        }

        val emailRequest = SendEmailRequest {
            destination = destinationOb
            message = msgOb
            source = "devbelly@naver.com"
        }

        client.use {
            println("Attempting to send an email through Amazon SES using the AWS SDK for Kotlin...")
            it.sendEmail(emailRequest)
        }
    }
}