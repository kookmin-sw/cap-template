package com.example.capstone.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import java.util.List;

@Getter
@AllArgsConstructor
@NoArgsConstructor
@Setter
@ToString
public class TmapPedestrianResponseDto {
    @JsonProperty("type")
    private String type;
    @JsonProperty("features")
    private List<Feature> features;


}
