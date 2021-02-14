package course.entity;

import javax.persistence.*;

@Entity
public class Auto {
    @Id
    @GeneratedValue(strategy= GenerationType.AUTO)
    private Integer id;

    private String num;
    private String color;
    private String mark;


    @ManyToOne(fetch = FetchType.EAGER) //каждый раз при получении сообщения сразу же получаем автора
    @JoinColumn(name = "user_id") //по умолчанию было бы author id, но сделали вот так
    private User person;

    public Auto() {
    }

    public Auto(String num, String color, String mark) {
        this.num = num;
        this.color = color;
        this.mark = mark;
        this.person = null;
    }

    public Auto(Integer id, String num, String color, String mark, User person) {
        this.id = id;
        this.num = num;
        this.color = color;
        this.mark = mark;
        this.person = person;
    }

    public Integer getId() {
        return id;
    }
    public void setId(Integer id) {
        this.id = id;
    }
    public String getNum() {
        return num;
    }
    public void setNum(String num) {
        this.num = num;
    }
    public String getColor() {
        return color;
    }
    public void setColor(String color) {
        this.color = color;
    }
    public String getMark() {
        return mark;
    }
    public void setMark(String mark) {
        this.mark = mark;
    }
    public User getPerson() {
        return person;
    }
    public void setPerson(User person) {
        this.person = person;
    }
}
