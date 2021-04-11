package com.company;

public class Timer {
    private long time;

    public Timer() {
        this.time = 0;
    }

    public void start() {
        time = System.currentTimeMillis();
        System.out.println("Timer start");
    }

    public void stop() {
        System.out.println("Timer stop");
        time = System.currentTimeMillis() - time;
        String timeout = time / 60000 + " min. " + (time % 60000) / 1000
                + " sec. " + (time % 60000) % 1000 + " ms.";
        System.out.println(timeout);
        time = 0;
    }
}
