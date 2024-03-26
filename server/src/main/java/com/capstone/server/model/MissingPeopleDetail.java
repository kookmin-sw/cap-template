package com.capstone.server.model;


//id integer [ ref: - missingPeople.id]
//  topColor varchar
//  topLength varchar
//  bottomColor varchar
//  bottomLength varchar
//  backpack string
//  handbag string
//  shoes string
//  cap string

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Entity(name = "missing_people_detail")
@EntityListeners(AuditingEntityListener.class)
public class MissingPeopleDetail {

    @Id
    @OneToOne
    @JoinColumn(name = "missing_people_id") // 외래 키 설정
    private MissingPeople missingPeople;
    private String topColor;
    private String topLength;

    private String bottomColor;
    private String bottomLength;

    private String bag;
    private String shoes;
    private String cap;
}
