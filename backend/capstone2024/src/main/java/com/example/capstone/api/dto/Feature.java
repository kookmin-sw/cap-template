package com.example.capstone.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class Feature {
    @JsonProperty("type")
    private String type;

    @JsonProperty("geometry")
    private Geometry geometry;

    @JsonProperty("properties")
    private Properties properties;

}
