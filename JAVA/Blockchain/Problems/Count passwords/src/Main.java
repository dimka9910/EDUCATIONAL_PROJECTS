import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Stream;

public class Main {

    /**
     * Returns the number of elements in a given stream.
     *
     * @param passwordStream the input stream of strings 
     * @return the number of elements in a given stream
     */
    public static long countPasswords(Stream<String> passwordStream) {
        // write your code here
        passwordStream = passwordStream.skip(2);
        return passwordStream.skip(2).count();
    }

    // Don't change the code below
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(countPasswords(Arrays.stream(scanner.nextLine().split("\\s+"))));
    }
}