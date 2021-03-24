import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;
import java.util.stream.Collectors;

class Main {

    /**
     * Returns joined list elements with '(' for the prefix
     * and ')' for the suffix.
     *
     * @param symbols the input list of String elements
     * @return the result of joining
     */
    public static String asciiArt(List<String> symbols) {
        //map(Objects::toString).
//        return symbols.stream().collect(Collectors.joining("","(",")"));
        var v = symbols.stream().collect(Collectors.to());
        // write your code here
    }


    // Don't change the code below
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> symbols = Arrays.asList(scanner.nextLine().split("\\s+"));
        System.out.println(asciiArt(symbols));
    }
}