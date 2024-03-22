package com.example.demo.dto;

import java.math.BigDecimal;

import com.example.demo.model.UserEntity;
import jakarta.validation.constraints.*;
import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class UserCreateRequestDto {

    @NotEmpty(message = "Name is required")
    private String name;

    @Positive(message = "Age is up to 0")
    @NotNull(message = "Age is required")
    private Integer age;

    // @Email(message = "Invalid email address")
    @NotEmpty(message = "Email is required")
    private String email;

    private BigDecimal latitude;

    private BigDecimal longitude;

    public UserEntity toEntity(){
        return UserEntity.builder().name(name).age(age).email(email).latitude(latitude).longitude(longitude).build();
    }
}
