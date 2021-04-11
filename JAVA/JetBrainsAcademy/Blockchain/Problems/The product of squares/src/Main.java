import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class CollectorProduct {

    public static void main(String[] args) {

        int[] n = {};
        System.out.println(IntStream.of(n).average());

//        Scanner scanner = new Scanner(System.in);
//
//        String[] values = scanner.nextLine().split(" ");
//
//        List<Integer> numbers = new ArrayList<>();
//        for (String val : values) {
//            numbers.add(Integer.parseInt(val));
//        }
//
//        long val = numbers.stream().collect(Collectors.reducing(1,(a,b) -> a = a * b * b)
//                    // Write your collector here
//                );
//
//        System.out.println(val);
//
//
    }
}