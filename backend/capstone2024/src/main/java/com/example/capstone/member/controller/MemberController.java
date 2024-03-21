package com.example.capstone.member.controller;

import com.example.capstone.member.dto.FavoriteRequest;
import com.example.capstone.member.dto.FavoriteResponse;
import com.example.capstone.member.dto.MemberCheckResponse;
import com.example.capstone.member.model.Favorite;
import com.example.capstone.member.model.Member;
import com.example.capstone.member.repository.FavoriteRepository;
import com.example.capstone.member.repository.MemberRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.sql.Timestamp;
import java.util.List;

@RestController
public class MemberController {

    @Autowired
    private MemberRepository memberRepository;

    @Autowired
    private FavoriteRepository favoriteRepository;

    @GetMapping("/checkMember")
    public ResponseEntity<MemberCheckResponse> checkMember(@RequestParam String uuid) {
        System.out.println("UUID: " + uuid);

        List<Member> memberList = memberRepository.findByUuid(uuid);
        if (!memberList.isEmpty()) {
            Member member = memberList.getFirst();
            System.out.println(member.toString());

            List<Favorite> favoriteList = favoriteRepository.findByMemberUuid(uuid);
            if (!favoriteList.isEmpty()) {
                System.out.println(favoriteList.toString());
                MemberCheckResponse response = new MemberCheckResponse(member, favoriteList);
                return ResponseEntity.ok(response);
            } else {
                System.out.println("즐겨찾기 X");
                MemberCheckResponse response = new MemberCheckResponse(member, null);
                return ResponseEntity.ok(response);
            }
        } else {
            Member newMember = new Member(uuid, new Timestamp(System.currentTimeMillis()));
            memberRepository.save(newMember);
            System.out.println("member 추가");

            MemberCheckResponse response = new MemberCheckResponse(newMember, null);
            System.out.println("즐겨찾기 X");
            return ResponseEntity.ok(response);
        }
    }
    @PostMapping("/addFavorite")
    public ResponseEntity<FavoriteResponse> addFavorite(
            @RequestBody FavoriteRequest favoriteRequest
    ) {
        System.out.println("UUID : " + favoriteRequest.getMemberUuid());
        System.out.println("즐겨찾기명 : " + favoriteRequest.getFavoriteName());
        System.out.println("도착지명 : " + favoriteRequest.getDestinationName());
        System.out.println("도착지좌표 : " + favoriteRequest.getDestinationCoordinates());

        List<Member> memberList = memberRepository.findByUuid(favoriteRequest.getMemberUuid());
        if (memberList.isEmpty()) {
            System.out.println("member X");
            return ResponseEntity.badRequest().body(new FavoriteResponse(null));
        }

        Member member = memberList.getFirst();

        Favorite newFavorite = new Favorite();
        newFavorite.setMemberUuid(favoriteRequest.getMemberUuid());
        newFavorite.setFavoriteName(favoriteRequest.getFavoriteName());
        newFavorite.setDestinationName(favoriteRequest.getDestinationName());
        newFavorite.setDestinationCoordinates(favoriteRequest.getDestinationCoordinates());
        newFavorite.setCreatedAt(new Timestamp(System.currentTimeMillis()));

        favoriteRepository.save(newFavorite);
        System.out.println("즐겨찾기 추가");

        FavoriteResponse response = new FavoriteResponse(newFavorite);
        return ResponseEntity.ok(response);
    }
}