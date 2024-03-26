package com.capstone.server.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import java.math.BigDecimal;
import java.time.LocalDateTime;


//
// id integer [primary key]
//  missingPeopleId id [not null]
//  searchStartTime datetime [not null]
//  searchEndTime datetime [not null]
//  logitude float [not null]
//  latitude float [not null]


@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
@Entity(name = "missing_people")
@EntityListeners(AuditingEntityListener.class)
public class SearchHistory {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @NotNull
    @ManyToOne
    @JoinColumn(name = "missing_people_id")
    private MissingPeople missingPeopleId;
    private LocalDateTime searchStartTime;
    private LocalDateTime searchEndTime;
    private BigDecimal latitude;
    private BigDecimal longitude;
}
