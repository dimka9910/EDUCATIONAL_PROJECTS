package engine.entity;


import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.security.core.context.SecurityContextHolder;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.Date;

@Entity
@Data
public class CompletedEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
    private int id_completed;


    @JsonProperty(access = JsonProperty.Access.WRITE_ONLY)
    @ManyToOne
    private UserEntity user;

    private int id;

    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)
    private Date completedAt;


    public CompletedEntity() {
        this.completedAt = new Date();
    }
}
//201 -31
//313 -3
//370