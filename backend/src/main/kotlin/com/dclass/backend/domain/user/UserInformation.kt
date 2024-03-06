package com.dclass.backend.domain.user

import jakarta.persistence.Column
import jakarta.persistence.Embeddable

@Embeddable
data class UserInformation(
    @Column(nullable = false, length = 30)
    val name: String,

    @Column(unique = true, nullable = false)
    val email: String,

    @Column(nullable = false, length = 13)
    val nickname: String
)