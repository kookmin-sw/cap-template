package com.example.capstone.api.service;

import org.springframework.stereotype.Service;
import org.springframework.web.util.UriComponentsBuilder;

import java.net.URI;

@Service
public class UriBuilderService {

    //좌표 변환
    private static final String TMAP_GEO_CODING_URL = "https://apis.openapi.sk.com/tmap/geo/fullAddrGeo";
    //보행자 경로 검색
    private static final String TMAP_PEDESTRAIN_URL = "https://apis.openapi.sk.com/tmap/routes/pedestrian";

    public URI buildUriGeoCodingByAddress(String address){
        UriComponentsBuilder uriBuilder = UriComponentsBuilder.fromHttpUrl(TMAP_GEO_CODING_URL);
        uriBuilder.queryParam("coordType", "WGS84GEO");
        uriBuilder.queryParam("fullAddr", address);
        uriBuilder.queryParam("addressFlag", "F00");

        URI uri = uriBuilder.build().encode().toUri();
        System.out.println("uri = " + uri);
        return uri;
    }

    //출발지 좌표값, 목적지 좌표값, 출발지 도착지 지명 필요
    public URI buildUriPedestrianByCoord(){
        UriComponentsBuilder uriBuilder = UriComponentsBuilder.fromHttpUrl(TMAP_PEDESTRAIN_URL);
        uriBuilder.queryParam("version","1");
        uriBuilder.queryParam("format","json");
        URI uri = uriBuilder.build().encode().toUri();
        System.out.println("uri = " + uri);
        return uri;
    }
}
