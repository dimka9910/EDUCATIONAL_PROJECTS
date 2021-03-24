package blockchain.testing;

public class SomeRunnable implements Runnable{

    private int j = 0;

    public SomeRunnable(int j) {
        this.j = j;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++){
            System.out.println("Runnable " + Thread.currentThread().getId() + " " + i + " " + j);
            j++;
        }
    }
}
