import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static boolean find(List<Integer> array){
        int i = 0;
        for (var v: array){
            if (v == i)
                return true;
            i++;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        List<Integer> array = new ArrayList<>();

        for (int i = 0; i < n; i++){
            array.add(scanner.nextInt());
        }
        System.out.println(find(array));
    }
}