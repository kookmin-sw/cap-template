package com.example.capstone.member.dto;

import com.example.capstone.member.model.Member;
import com.example.capstone.member.model.Favorite;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import java.util.List;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class MemberCheckResponse {
    private Member member;
    private List<Favorite> favorites;
}