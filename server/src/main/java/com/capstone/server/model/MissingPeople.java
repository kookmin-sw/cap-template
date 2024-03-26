package com.capstone.server.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.Date;

//Table missingPeople {
//  id integer [primary key]
//  name varchar [not null]
//  age integer [not null]
//  gender varchar [not null]
//  missingAt datetime
//  registrationAt datetime [not null]
//  guardianId integer [not null]
//}
@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Entity(name = "missing_people")
@EntityListeners(AuditingEntityListener.class)
public class MissingPeople {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "missing_people_id")
    private Long id;

    @NotNull
    private String name;

    @NotNull
    private Integer age;

    @NotNull
    private String email;


    private BigDecimal latitude;

    private BigDecimal longitude;

    @NotNull
    private Date createdAt;

    @NotNull
    private Date updatedAt;

    @CreatedDate
    private LocalDateTime localDate;

    @NotNull
    private String gender;

    @NotNull
    private LocalDateTime missingAt;

    @NotNull
    @OneToOne
    @JoinColumn(name = "guardian_id")
    private MissingPeopleGuardian guardianId;

    @PrePersist
    protected void onCreate() {
        createdAt = new Date();
        updatedAt = new Date();
        localDate = LocalDateTime.now();
    }

    @PreUpdate // 업데이트가 발생할 때 호출되는 메소드
    protected void onUpdate() {
        updatedAt = new Date();
    }

}
