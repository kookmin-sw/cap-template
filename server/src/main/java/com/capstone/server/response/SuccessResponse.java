package com.example.demo.response;

import java.time.LocalDateTime;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@Getter
@AllArgsConstructor
@RequiredArgsConstructor
public class SuccessResponse<T> {
    private final LocalDateTime timestamp = LocalDateTime.now();
    private int statusCode = 200;
    private boolean success = true;
    private final T data = null;
}