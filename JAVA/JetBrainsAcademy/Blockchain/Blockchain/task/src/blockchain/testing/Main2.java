package blockchain.testing;


import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main2 {

    private static final int POOL_SIZE = Runtime.getRuntime().availableProcessors();

    public static void main(String[] args) {
        Thread thread = new Thread(new SomeRunnable(1));// passing runnable
        Thread thread1 = new SomeThread(3); // a subclass of Thread

        //thread.start();
        //thread1.start();

        ExecutorService executor = Executors.newFixedThreadPool(POOL_SIZE);

        /** All of That is
         * possible */
        //executor.submit(new SomeRunnable(1));
        //executor.submit(new Thread(new SomeRunnable(1)));
        //executor.submit(thread);
        //executor.submit(thread1);



        executor.shutdown();

    }
}
