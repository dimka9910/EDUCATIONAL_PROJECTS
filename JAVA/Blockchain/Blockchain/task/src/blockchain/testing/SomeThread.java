package blockchain.testing;

public class SomeThread extends Thread {
    private int j = 0;

    public SomeThread(int j) {
        this.j = j;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++){
            j++;
            System.out.println("Thread " + Thread.currentThread().getId() + " " + i + " " + j);
        }
    }
}
