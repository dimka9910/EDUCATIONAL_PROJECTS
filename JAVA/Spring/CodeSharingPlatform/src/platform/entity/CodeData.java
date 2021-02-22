package platform.entity;



import com.fasterxml.jackson.annotation.JsonIgnore;

import javax.persistence.Entity;
import javax.persistence.Id;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.util.UUID;

@Entity
public class CodeData {

    @Id
    @JsonIgnore
    private UUID id = UUID.randomUUID();

    private String code;

    private LocalDateTime date;

    private Long time;

    @JsonIgnore
    private boolean timeRestriction;

    private Long views;

    @JsonIgnore
    private boolean viewsRestriction;

    public CodeData() {
    }

    public CodeData(String code) {
        this.code = code;
        date = LocalDateTime.now();
    }

    public CodeData(CodeData codeData) {
        this.code = codeData.code;
        date = LocalDateTime.now();
        this.time = codeData.time;
        this.views = codeData.views;
        this.viewsRestriction = (codeData.views > 0);
        this.timeRestriction = (codeData.time > 0);
    }

    public Long getTime() {
        return timeRestriction ? time - ChronoUnit.SECONDS.between(date, LocalDateTime.now()) : time;
    }

    public void setTime(Long time) {
        this.time = time;
    }

    public boolean isTimeRestriction() {
        return timeRestriction;
    }

    public void setTimeRestriction(boolean timeRestriction) {
        this.timeRestriction = timeRestriction;
    }

    public Long getViews() {
        return views;
    }

    public void setViews(Long views) {
        this.views = views;
    }

    public boolean isViewsRestriction() {
        return viewsRestriction;
    }

    public void setViewsRestriction(boolean viewsRestriction) {
        this.viewsRestriction = viewsRestriction;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getDate() {
        return date.format(DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss"));
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String toString(){
        return id + "\n" + timeRestriction + "\n" + viewsRestriction + "\n" + time + "\n" + views;
    }
}
