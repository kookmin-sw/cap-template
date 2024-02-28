package com.dclass.backend.domain.department

import com.dclass.support.domain.BaseEntity
import jakarta.persistence.Column
import jakarta.persistence.Entity

@Entity
class Department(
    @Column(nullable = false)
    val title: String = "",
    id: Long = 0L
) : BaseEntity(id)