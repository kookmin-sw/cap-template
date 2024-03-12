package com.capstone.server.controller;

import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.List;

@Slf4j
@RestController

public class TestController {
    @GetMapping("/tests")
    public List<String> getTest() {
        log.info("sdf");
        return Arrays.asList("test", "success");
    }
}
