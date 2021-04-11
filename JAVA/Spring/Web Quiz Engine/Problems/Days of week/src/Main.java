// declare your enum here

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

enum DayOfWeek {
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY;

    public String f(){
        System.out.println(this);
        return "lol";
    }
}

public class Main {
    public static void main(String[] args) {
        Deque<String> states = new ArrayDeque<String>();
        states.add("A");
        states.addLast("B");
        states.offer("C");
        states.offerLast("D");
        System.out.println(states);

        states.push("E");
        System.out.println(states);
    }
}


