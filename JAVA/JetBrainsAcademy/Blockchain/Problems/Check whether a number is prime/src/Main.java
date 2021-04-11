import java.util.Scanner;
import java.util.concurrent.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ExecutorService executor = Executors.newCachedThreadPool(); // assign an object to it

        while (scanner.hasNext()) {
            int number = scanner.nextInt();
            executor.submit(() -> {
                Thread r = new Thread(new PrintIfPrimeTask(number));
                r.start();
                 // do not change it
            });
            // create and submit tasks
        }
        executor.shutdown();
    }
}

class PrintIfPrimeTask implements Runnable {
    private final int number;

    public PrintIfPrimeTask(int number) {
        this.number = number;
    }

    @Override
    public void run() {
        boolean t = true;

        if (number == 1){

            t = false;
        }

        for (int i = 2; i < number; i++)
        {
            //System.out.println("# " + Thread.currentThread().getId());
            if (number % i == 0){
                t = false;
            }
        }

        if (t)
            System.out.println(number);
        // write code of task here
    }
}