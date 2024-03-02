package com.dclass.backend.domain.blacklist

import com.dclass.support.domain.BaseEntity
import jakarta.persistence.Column
import jakarta.persistence.Entity

@Entity
class Blacklist(
    @Column(nullable = false)
    val invalidRefreshToken: String,
    id: Long = 0L
) : BaseEntity(id)