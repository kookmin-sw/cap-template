package com.dclass.support.domain

import jakarta.persistence.Column
import jakarta.persistence.Embeddable
import java.net.URL

@Embeddable
class Image(
    @Column(nullable = false)
    val key: String
)
