import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) {

        Stream.of(1, 2, 1, 3, 2, 4).collect(Collectors.groupingBy(Function.identity()))
                .entrySet().stream().forEach(System.out::println);

//        Arrays.stream(new Scanner(System.in).nextLine().split("\\s+"))
//                .map(s -> s.replaceAll("[^A-Za-z0-9]", ""))
//                .sorted()
//                .map(String::toLowerCase)
//                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()))
//                .entrySet().stream()
//                .sorted(Map.Entry.comparingByKey())
//                .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
//                .limit(10)
//                .map(Map.Entry::getKey)
//                .forEach(System.out::println);
    }
}