package com.example.capstone.member.controller;

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
    public String addFavorite(
            @RequestParam String uuid,
            @RequestParam String favoriteName,
            @RequestParam String destinationName,
            @RequestParam String destinationCoordinates
    ) {
        System.out.println("UUID: " + uuid);
        System.out.println("즐겨찾기명: " + favoriteName);
        System.out.println("도착지명: " + destinationName);
        System.out.println("도착지좌표" + destinationCoordinates);

        List<Member> memberList = memberRepository.findByUuid(uuid);
        if (memberList.isEmpty()) {
            return "UUID 없음 : " + uuid;
        }

        Member member = memberList.getFirst();

        Favorite newFavorite = new Favorite();
        newFavorite.setMemberUuid(uuid);
        newFavorite.setFavoriteName(favoriteName);
        newFavorite.setDestinationName(destinationName);
        newFavorite.setDestinationCoordinates(destinationCoordinates);
        newFavorite.setCreatedAt(new Timestamp(System.currentTimeMillis()));

        favoriteRepository.save(newFavorite);

        return "즐겨찾기 추가 완료 :\n" + newFavorite.toString();
    }
}