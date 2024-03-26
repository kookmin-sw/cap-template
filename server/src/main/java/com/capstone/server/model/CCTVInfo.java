package com.capstone.server.model;


import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import java.math.BigDecimal;

//
// id integer [primary key]
//  logitude float [not null]
//  latitude float [not null]
@Data
@AllArgsConstructor
@Builder
@Entity(name = "cctv_info")
@EntityListeners(AuditingEntityListener.class)
public class CCTVInfo {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private BigDecimal latitude;
    private BigDecimal longitude;

}
