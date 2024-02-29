package com.dclass.backend.ui.api

import com.dclass.backend.application.UserAuthenticationService
import com.dclass.backend.application.UserService
import com.dclass.backend.application.mail.MailService
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.RequestMapping
import org.springframework.web.bind.annotation.RequestParam
import org.springframework.web.bind.annotation.RestController

@RequestMapping("/api/users")
@RestController
class UserRestController(
    private val userService: UserService,
    private val userAuthenticationService: UserAuthenticationService,
    private val mailService: MailService
) {

    @PostMapping("/authentication-code")
    fun generateAuthenticationCode(
        @RequestParam email: String
    ): ResponseEntity<Unit> {
        val authenticationCode = userAuthenticationService
            .generateAuthenticationCode(email)
        mailService.sendAuthenticationCodeMail(email, authenticationCode)
        return ResponseEntity.noContent().build()
    }

    @PostMapping("/authenticate-email")
    fun authenticateEmail(
        @RequestParam email: String,
        @RequestParam authenticationCode: String
    ): ResponseEntity<Unit> {
        userAuthenticationService.authenticateEmail(email, authenticationCode)
        return ResponseEntity.noContent().build()
    }
}