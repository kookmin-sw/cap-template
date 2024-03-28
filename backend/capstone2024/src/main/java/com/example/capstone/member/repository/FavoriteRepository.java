package com.example.capstone.member.repository;

import com.example.capstone.member.model.Favorite;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.List;

public interface FavoriteRepository extends JpaRepository<Favorite, Long> {
    List<Favorite> findByMemberUuid(String memberUuid);
}
