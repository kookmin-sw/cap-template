package com.example.demo.exception;

import java.util.Map;

import com.example.demo.code.UserErrorCode;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@Getter
@RequiredArgsConstructor
@AllArgsConstructor
public class UserException extends RuntimeException {
    private final UserErrorCode errorCode;
    private Map<String, String> errorDetailsMapping;
    private Exception errorDetails;

    public UserException(UserErrorCode errorCode, Map<String, String> errorDetailsMapping) {
        this.errorCode = errorCode;
        this.errorDetailsMapping = errorDetailsMapping;
    }

    public UserException(UserErrorCode errorCode, Exception errorDetails) {
        this.errorCode = errorCode;
        this.errorDetails = errorDetails;
    }
}