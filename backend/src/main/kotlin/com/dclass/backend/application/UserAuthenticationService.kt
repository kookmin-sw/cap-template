package com.dclass.backend.application

import com.dclass.backend.domain.authenticationcode.AuthenticationCode
import com.dclass.backend.domain.authenticationcode.AuthenticationCodeRepository
import com.dclass.backend.domain.authenticationcode.getLastByEmail
import com.dclass.backend.domain.user.UniversityRepository
import com.dclass.backend.domain.user.UserRepository
import com.dclass.backend.domain.user.existsByEmail
import com.dclass.backend.security.JwtTokenProvider
import org.springframework.stereotype.Service
import org.springframework.transaction.annotation.Transactional

@Transactional
@Service
class UserAuthenticationService(
    private val userRepository: UserRepository,
    private val authenticationCodeRepository: AuthenticationCodeRepository,
    private val universityRepository: UniversityRepository,
) {

    fun generateAuthenticationCode(email: String): String {
        check(!userRepository.existsByEmail(email)) { "이미 등록된 이메일입니다." }
        check(universityRepository.existsByEmailSuffix(getEmailSuffix(email))) { "이메일이 등록되지 않은 대학교입니다." }
        val authenticationCode = authenticationCodeRepository.save(AuthenticationCode(email))
        return authenticationCode.code
    }

    fun authenticateEmail(email: String, code: String) {
        val authenticationCode = authenticationCodeRepository.getLastByEmail(email)
        authenticationCode.authenticate(code)
    }

    private fun getEmailSuffix(email: String): String {
        return email.substringAfterLast("@")
    }
}