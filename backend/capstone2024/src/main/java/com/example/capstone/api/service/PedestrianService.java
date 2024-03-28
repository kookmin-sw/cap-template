package com.example.capstone.api.service;

import com.example.capstone.api.dto.TmapGeoCodingResponseDto;
import com.example.capstone.api.dto.TmapPedestrianResponseDto;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.util.ObjectUtils;
import org.springframework.web.client.RestTemplate;

import java.net.URI;

@Service
@RequiredArgsConstructor
public class PedestrianService {
    private final RestTemplate restTemplate;
    private final UriBuilderService uriBuilderService;
    private final GeoCodingService geoCodingService;
    private final ObjectMapper objectMapper;
    private static final String APPKEY = "qnMdq4E5hK6Jiying7vO84rBBYBMqE0L8JibODZN";

    public TmapPedestrianResponseDto requestPedestrian(String startAddress, String endAddress) throws Exception{
        if (ObjectUtils.isEmpty(startAddress) || ObjectUtils.isEmpty(endAddress)) return null;
        //lon 경도 X
        //lat 위도 Y

        TmapGeoCodingResponseDto tmapGeoCodingResponseDto = geoCodingService.requestGeoCoding(startAddress);
        String startNewLat = tmapGeoCodingResponseDto.getCoordinateInfo().getCoordinate().getFirst().getNewLat();
        String startNewLon = tmapGeoCodingResponseDto.getCoordinateInfo().getCoordinate().getFirst().getNewLon();

        TmapGeoCodingResponseDto tmapGeoCodingResponseDto2 = geoCodingService.requestGeoCoding(endAddress);
        String endNewLat = tmapGeoCodingResponseDto2.getCoordinateInfo().getCoordinate().getFirst().getNewLat();
        String endNewLon = tmapGeoCodingResponseDto2.getCoordinateInfo().getCoordinate().getFirst().getNewLon();

        System.out.println("startNewLat = " + startNewLat);
        System.out.println("startNewLon = " + startNewLon);
        System.out.println("endNewLat = " + endNewLat);
        System.out.println("endNewLon = " + endNewLon);
        URI uri = uriBuilderService.buildUriPedestrianByCoord();

        HttpHeaders headers = new HttpHeaders();
        headers.add("appKey",APPKEY);

        MultiValueMap<String, String> params = new LinkedMultiValueMap<>();
        params.add("startX",startNewLon);
        params.add("startY",startNewLat);
        params.add("endX",endNewLon);
        params.add("endY",endNewLat);
        params.add("reqCoordType","WGS84GEO");
        params.add("resCoordType","WGS84GEO");
        params.add("startName",startAddress);
        params.add("endName",endAddress);



        HttpEntity<MultiValueMap<String, String>> entity = new HttpEntity<>(params, headers);
        //api 호출
        //추후에 바디 변경 필요
//        TmapPedestrianResponseDto body = restTemplate.exchange(uri, HttpMethod.POST, entity, TmapPedestrianResponseDto.class).getBody();
//        return body;
        // API 호출 및 응답 받기 (String 형태로)
        String rawResponse = restTemplate.exchange(uri, HttpMethod.POST, entity, String.class).getBody();

        // 불법 문자 전처리 (예제: Null 문자 제거)
        String cleanedResponse = rawResponse.replace("\u0000", "");

        // 전처리된 응답을 DTO로 변환
        TmapPedestrianResponseDto responseDto = objectMapper.readValue(cleanedResponse, TmapPedestrianResponseDto.class);
        return responseDto;
    }

}
