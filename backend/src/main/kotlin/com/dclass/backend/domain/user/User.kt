package com.dclass.backend.domain.user

import com.dclass.support.domain.BaseRootEntity
import jakarta.persistence.AttributeOverride
import jakarta.persistence.Column
import jakarta.persistence.Embedded
import jakarta.persistence.Entity

@Entity
class User(

    @Embedded
    private var information: UserInformation,

    @AttributeOverride(name = "value", column = Column(name = "password", nullable = false))
    @Embedded
    var password: Password,

    id: Long = 0L
) : BaseRootEntity<User>(id) {

    val name: String
        get() = information.name

    val email: String
        get() = information.email

    val nickname: String
        get() = information.nickname

    constructor(
        name: String,
        email: String,
        nickname: String,
        password: Password,
        id: Long = 0L
    ) : this(
        UserInformation(name, email, nickname), password, id
    )

    fun authenticate(password: Password) {
        require(password == this.password) { "사용자 정보가 일치하지 않습니다." }
    }
}