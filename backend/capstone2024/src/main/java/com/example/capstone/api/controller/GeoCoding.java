package com.example.capstone.api.controller;

import com.example.capstone.api.service.GeoCodingService;
import com.example.capstone.api.service.PedestrianService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
public class GeoCoding {

    private final GeoCodingService geoCodingService;
    private final PedestrianService pedestrianService;
    @GetMapping("/test")
    public String testGPS(@RequestParam(value = "address") String address){
        return geoCodingService.requestGeoCoding(address).toString();
    }

    @GetMapping("/testpede")
    public String testPede(@RequestParam(value = "startAddress") String startAddress,@RequestParam(value = "endAddress") String endAddress) throws Exception {
        System.out.println("startAddress = " + startAddress);
        System.out.println("endAddress = " + endAddress);
        return pedestrianService.requestPedestrian(startAddress,endAddress).toString();
    }

}
