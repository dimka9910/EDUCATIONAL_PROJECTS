package org.example.dto;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class AutoDto {

    private Integer id;
    private String num;
    private String color;
    private String mark;
    private Integer personnel_id;
}
