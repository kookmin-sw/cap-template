package com.example.capstone.member.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.Getter;
import lombok.Setter;

import java.sql.Timestamp;

@Setter
@Getter
@Entity
public class Favorite {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String memberUuid;
    private String favoriteName;
    private String destinationName;
    private String destinationCoordinates;
    private Timestamp createdAt;

    public Favorite() {

    }

    @Override
    public String toString() {
        return "Favorite{" +
                "id=" + id +
                ", memberUuid='" + memberUuid + '\'' +
                ", favoriteName='" + favoriteName + '\'' +
                ", destinationName='" + destinationName + '\'' +
                ", destinationCoordinates='" + destinationCoordinates + '\'' +
                ", createdAt=" + createdAt +
                '}';
    }
}
