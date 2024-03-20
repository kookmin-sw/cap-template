package com.example.capstone.member.model;

import java.sql.Timestamp;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
@Entity
public class Member {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String uuid;
    private Timestamp createdAt;


    public Member() {
    }

    public Member(String uuid, Timestamp createdAt) {
        this.uuid = uuid;
        this.createdAt = createdAt;
    }

    public Member(Long id, String uuid, Timestamp createdAt) {
        this.id = id;
        this.uuid = uuid;
        this.createdAt = createdAt;
    }

    @Override
    public String toString() {
        return "Member{" +
                "id=" + id +
                ", uuid='" + uuid + '\'' +
                ", createdAt=" + createdAt +
                '}';
    }

}