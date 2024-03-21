package com.example.capstone.member.dto;

import com.example.capstone.member.model.Favorite;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class FavoriteResponse {
    private String message;
    private Favorite favorite;
}