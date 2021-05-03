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
        double k = 11;
        double r1 = 1 + 6 / (k + 6);
        double r3 = r1, r2 = 0.5,  r4 = 0.1;
        r1 =0.5;
        System.out.println(r1);

        double n = 5 + 2 * r1 * (4 / r2 - 1 / r4);
        double u = 1 - 0.03 * r4;
        double P = 20 / r1 + 10 / r2;
        double tz = 0.5 + 0.1*r2/r4 + r2 * (6 + 0.1 * n) + 7 / (8 + 3 * r3);
        double s = 10 * r2 / r1;

        System.out.println(n);
        System.out.println(u);
        System.out.println(P);
        System.out.println(tz);
        System.out.println(s);

        System.out.println();

        n = -n;
        u = -u;
        s = -s;

        n = (-n - 20.0)/(0.2 * 20.0) + 1;
        u = (-u - 0.8)/(0.2 * 0.8) + 1;
        P= (-P+20) / (0.2 *20) -1;
        tz=(-tz+15) / (0.2 * 15) - 1;
        s=(-s - 1.5) / (0.2 * 1.5) + 1;
        System.out.println(n);
        System.out.println(u);
        System.out.println(P);
        System.out.println(tz);
        System.out.println(s);


    }
}


