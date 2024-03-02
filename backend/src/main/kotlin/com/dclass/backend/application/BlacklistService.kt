package com.dclass.backend.application

import com.dclass.backend.application.dto.LoginUserResponse
import com.dclass.backend.domain.blacklist.Blacklist
import com.dclass.backend.domain.blacklist.BlacklistRepository
import com.dclass.backend.security.JwtTokenProvider
import org.springframework.stereotype.Service
import org.springframework.transaction.annotation.Transactional


@Transactional
@Service
class BlacklistService(
    private val blacklistRepository: BlacklistRepository,
    private val jwtTokenProvider: JwtTokenProvider,
) {
    fun reissueToken(refreshToken: String): LoginUserResponse {
        require(jwtTokenProvider.isValidToken(refreshToken)) { "유효하지 않은 토큰입니다." }
        blacklistRepository.findByInvalidRefreshToken(refreshToken)
            ?.let { throw IllegalArgumentException("이미 로그아웃한 사용자입니다.") }
            ?: blacklistRepository.save(Blacklist(refreshToken))

        val email = jwtTokenProvider.getSubject(refreshToken)
        return LoginUserResponse(
            jwtTokenProvider.createAccessToken(email),
            jwtTokenProvider.createRefreshToken(email)
        )
    }
}