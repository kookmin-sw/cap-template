package com.capstone.server.exception;

import java.util.Map;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.servlet.mvc.method.annotation.ResponseEntityExceptionHandler;
import com.capstone.server.code.UserErrorCode;
import com.example.demo.response.ErrorResponse;

@RestControllerAdvice
public class GlobalExceptionHandler extends ResponseEntityExceptionHandler {

    /*
     * Developer Custom Exception: 직접 정의한 RestApiException 에러 클래스에 대한 예외 처리
     */
    @ExceptionHandler(UserException.class)
    protected ResponseEntity<ErrorResponse> handleCustomException(UserException ex) {
        UserErrorCode errorCode = ex.getErrorCode();
        Map<String, String> errorDetails = ex.getErrorDetailsMapping();
        if (errorDetails != null) {
            System.out.println(errorDetails);
            return handleExceptionFromValidation(errorCode, errorDetails);
        }
        
        return handleExceptionInternal(errorCode);
    };

	// handleExceptionInternal() 메소드를 오버라이딩해 응답 커스터마이징
    private ResponseEntity<ErrorResponse> handleExceptionInternal(UserErrorCode errorCode) {
        return ResponseEntity
                .status(errorCode.getHttpStatus().value())
                .body(new ErrorResponse(errorCode));
    }

    private ResponseEntity<ErrorResponse> handleExceptionFromValidation(UserErrorCode errorCode, Map<String, String> errorDetails) {
        return ResponseEntity
                .status(errorCode.getHttpStatus().value())
                .body(new ErrorResponse(errorCode, errorDetails));
    }
}