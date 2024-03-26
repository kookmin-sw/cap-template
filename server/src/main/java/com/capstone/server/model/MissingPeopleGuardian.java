package com.capstone.server.model;


import jakarta.persistence.*;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

//id integer [primary key]
//  name varchar [not null]
//  phoneNumber varchar [not null]
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Entity(name = "missing_people_guardian")
@EntityListeners(AuditingEntityListener.class)
public class MissingPeopleGuardian {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "guardian_id")
    private Long id;

    @NotNull
    private String name;
    private String phoneNumber;
}
