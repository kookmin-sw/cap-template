package com.capstone.capstone.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import java.sql.Timestamp;

@Entity
public class Member {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String uuid;
    private Timestamp createdAt;


    public Long getId() {
        return id;
    }

    public String getUuid() {
        return uuid;
    }

    public Timestamp getCreatedAt() {
        return createdAt;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public void setCreatedAt(Timestamp createdAt) {
        this.createdAt = createdAt;
    }

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
