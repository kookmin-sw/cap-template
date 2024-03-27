package com.example.capstone.member.dto;

import lombok.Data;

@Data
public class FavoriteRequest {
    private String memberUuid;
    private String favoriteName;
    private String destinationName;
    private String destinationCoordinates;
}