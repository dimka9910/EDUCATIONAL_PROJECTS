import java.util.Arrays;
import java.util.stream.IntStream;

class Starter {

    public static void startRunnables(Runnable[] runnables) {
        IntStream.range(0, runnables.length).forEach(v ->
                new Thread(runnables[v]).start());
        // implement the method
    }
}