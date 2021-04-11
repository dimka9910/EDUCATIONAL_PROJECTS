import java.lang.reflect.Array;
import java.util.*;

public class Main {

    public static void moveThePivot(int[] array, int pivotIndex) {
        Arrays.sort(array);
        // write your code here
    }

    /* Do not change code below */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = Arrays.stream(scanner.nextLine().split(" "))
                .mapToInt(Integer::parseInt).toArray();
        int pivotIndex = scanner.nextInt();
        moveThePivot(array, pivotIndex);
        Arrays.stream(array).forEach(e -> System.out.print(e + " "));
    }
}