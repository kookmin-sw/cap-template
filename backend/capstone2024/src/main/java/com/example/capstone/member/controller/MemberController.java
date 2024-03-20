package com.example.capstone.member.controller;

import com.example.capstone.member.model.Favorite;
import com.example.capstone.member.model.Member;
import com.example.capstone.member.repository.FavoriteRepository;
import com.example.capstone.member.repository.MemberRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.sql.Timestamp;
import java.util.List;

@RestController
//@RequestMapping("/api") // 변경된 부분
public class MemberController {

    @Autowired
    private MemberRepository memberRepository;

    @Autowired
    private FavoriteRepository favoriteRepository;

    @GetMapping("/checkMember")
    public String checkMember(@RequestParam String uuid) {
        System.out.println("UUID: " + uuid);

        List<Member> memberList = memberRepository.findByUuid(uuid);
        if (!memberList.isEmpty()) {
            Member member = memberList.getFirst(); // getFirst() 대신에 get(0) 사용
            System.out.println("member table에 있음 : " + member.toString());

            List<Favorite> favoriteList = favoriteRepository.findByMemberUuid(uuid);
            if (!favoriteList.isEmpty()) {
                System.out.println("Favorite에 있음 : " + favoriteList.toString());
                return "멤버 추가 x Member : " + member.toString() + "\nFavorite에 있음 : " + favoriteList.toString();
            } else {
                System.out.println("Member에 있음 : " + member.toString());
                System.out.println("Favorite에 없음 : ");
                return "멤버 추가 x Member : " + member.toString() + "\n Favorite에 없음 : " + uuid;
            }
        } else {
            Member newMember = new Member(uuid, new Timestamp(System.currentTimeMillis()));
            memberRepository.save(newMember);

            return "Member 추가 : " + newMember.toString();
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