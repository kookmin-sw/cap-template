package com.dclass.support.domain

import jakarta.persistence.Column
import jakarta.persistence.Embeddable
import java.net.URL

@Embeddable
class Image(
    @Column(nullable = false)
    val url: String
) {
    init {
        validateUrl(url)
    }

    private fun validateUrl(url: String) {
        try {
            URL(url)
        } catch (e: Exception) {
            throw IllegalArgumentException("올바른 형식의 URL이 아닙니다. $url")
        }
    }
}