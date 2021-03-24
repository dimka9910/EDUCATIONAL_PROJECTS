import java.util.*;

public class Main {

    /**
     * Counts the number of unique words ignoring case sensitivity
     * for given lines with words.
     *
     * @param n     the n lines contain words
     * @param lines the list of lines, each line is a list of words
     * @return the number of unique words in lines ignoring case sensitivity
     */

    /**
     * Count the number of unique words
     * ignoring case sensitivity for given lines with words.
     *
     * The first line contains the number n.
     * The next n lines contain words separated by a space.
     *
     * 3
     * Word word wORD
     * line Line SplinE word
     * spline align Java java
     */
    public static long count(int n, List<List<String>> lines) {
        return lines.stream()
                .limit(n)
                .flatMap(x -> x.stream())
                .map(x -> x.toUpperCase())
                .distinct()
                .count();
    }

    // Don't change the code below
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = Integer.parseInt(scanner.nextLine());

        List<List<String>> lines = new ArrayList<>();
        String line;
        while (scanner.hasNextLine() && !(line = scanner.nextLine()).isEmpty()) {
            lines.add(Arrays.asList(line.split("\\s+")));
        }

        System.out.println(count(n, lines));
    }
}