package blockchain.testing2;

import java.util.ArrayList;
import java.util.List;


class Team {
}

class Player {
    public Team team;

    public Player(Team team) {
        this.team = team;
    }
}


abstract class Engine {
}

class Car {
    Engine engine;

    public Car(Engine eng) {
        engine = eng;
    }
}

class User {
    public int Id;
    public String name;
}

class Manager extends User {
    public String company;
}


public class Main3 {
    public static void main(String[] args) {


    }
}
