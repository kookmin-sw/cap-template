package com.example.capstone.member.repository;


import com.example.capstone.member.model.Member;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface MemberRepository extends JpaRepository<Member, Long> {
    List<Member> findByUuid(String uuid);
}