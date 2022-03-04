import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<Integer> list = List.of(4,2,3,2);

        list.stream().filter(Main::f).map(Main::m).peek(System.out::println).filter(Main::f).reduce(0, (a,b) -> a+b);

    }

    public static boolean f(Integer a){
        System.out.println("f" + a);
        return a > 1;
    }

    public static Integer m(Integer a){
        System.out.println("m" + a);
        return a - 1;
    }
}
