package com.dclass.backend.domain.user

import jakarta.persistence.Embeddable

@Embeddable
data class Password(
    var value: String
)