package platform;

import com.fasterxml.jackson.databind.annotation.JsonSerialize;

@JsonSerialize
public class Answer {
    private int id;

    public Answer(int id) {
        this.id = id;
    }

    public String getId() {
        return String.valueOf(id);
    }

    public void setId(int id) {
        this.id = id;
    }
}
