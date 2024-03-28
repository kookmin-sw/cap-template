package com.example.capstone.member.model;

import java.sql.Timestamp;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
@Entity
public class Member {

    @Id
    private String uuid;

    @Column(name = "created_at")
    private Timestamp createdAt;

    public Member() {
    }

    public Member(String uuid, Timestamp createdAt) {
        this.uuid = uuid;
        this.createdAt = createdAt;
    }

    @Override
    public String toString() {
        return "Member{" +
                ", uuid='" + uuid + '\'' +
                ", createdAt=" + createdAt +
                '}';
    }

}