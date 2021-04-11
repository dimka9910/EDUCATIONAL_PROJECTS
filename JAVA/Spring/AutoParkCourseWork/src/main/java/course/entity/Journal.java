package course.entity;

import org.springframework.format.annotation.DateTimeFormat;

import javax.persistence.*;
import java.sql.Timestamp;
import java.util.Date;

@Entity
public class Journal {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)
    private Date time_out;
    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)
    private Date time_in;

    @ManyToOne(fetch = FetchType.EAGER) //каждый раз при получении сообщения сразу же получаем автора
    @JoinColumn(name = "auto_id") //по умолчанию было бы author id, но сделали вот так
    private Auto auto;

    @ManyToOne(fetch = FetchType.EAGER) //каждый раз при получении сообщения сразу же получаем автора
    @JoinColumn(name = "route_id") //по умолчанию было бы author id, но сделали вот так
    private Routes route;


    public Journal() {
    }

    public Journal(Auto auto, Routes route) {
        this.auto = auto;
        this.route = route;
        this.time_out = new Date();
    }

    public Journal(Long id, Date time_out, Auto auto, Routes route) {
        this.id = id;
        this.time_out = time_out;
        this.time_in = new Date();
        this.auto = auto;
        this.route = route;
    }

    public Journal(Date time_out, Date time_in, Auto auto, Routes route) {
        this.time_out = time_out;
        this.time_in = time_in;
        this.auto = auto;
        this.route = route;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Date getTime_out() {
        return time_out;
    }

    public void setTime_out(Timestamp time_out) {
        this.time_out = time_out;
    }

    public Date getTime_in() {
        return time_in;
    }

    public void setTime_in(Timestamp time_in) {
        this.time_in = time_in;
    }

    public Auto getAuto() {
        return auto;
    }

    public void setAuto(Auto auto) {
        this.auto = auto;
    }

    public Routes getRoute() {
        return route;
    }

    public void setRoute(Routes route) {
        this.route = route;
    }
}
