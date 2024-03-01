package com.dclass.backend.security

import io.jsonwebtoken.JwtException
import io.jsonwebtoken.Jwts
import io.jsonwebtoken.SignatureAlgorithm
import io.jsonwebtoken.security.Keys
import org.springframework.stereotype.Component
import java.util.*
import javax.crypto.SecretKey

@Component
class JwtTokenProvider(
    private val signingKey: SecretKey = Keys.secretKeyFor(SignatureAlgorithm.HS256),
) {
    companion object {
        const val ACCESS_TOKEN_EXPIRATION_MILLISECONDS: Long = 1000 * 60 * 60 * 1 // 1시간
        const val REFRESH_TOKEN_EXPIRATION_MILLISECONDS: Long = 1000 * 60 * 60 * 24 * 14 // 2주
    }

    fun createAccessToken(payload: String): String {
        return createToken(payload, ACCESS_TOKEN_EXPIRATION_MILLISECONDS)
    }

    fun createRefreshToken(payload: String): String {
        return createToken(payload, REFRESH_TOKEN_EXPIRATION_MILLISECONDS)
    }

    fun createToken(payload: String, validity: Long): String {
        return Jwts.builder()
            .setSubject(payload)
            .setExpiration(Date(System.currentTimeMillis() + validity))
            .signWith(signingKey)
            .compact()
    }

    fun getSubject(token: String): String {
        return getClaimsJws(token)
            .body
            .subject
    }

    fun isValidToken(token: String): Boolean {
        return try {
            getClaimsJws(token)
            true
        } catch (e: JwtException) {
            false
        } catch (e: IllegalArgumentException) {
            false
        }
    }

    private fun getClaimsJws(token: String) = Jwts.parserBuilder()
        .setSigningKey(signingKey.encoded)
        .build()
        .parseClaimsJws(token)
}