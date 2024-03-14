package com.example.capstone.api.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.List;

@Data
public class Geometry {
    @JsonProperty("type")
    private String type;
    @JsonProperty("coordinates")
    private Object coordinates;

}
