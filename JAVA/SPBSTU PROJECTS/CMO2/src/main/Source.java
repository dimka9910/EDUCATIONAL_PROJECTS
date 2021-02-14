package main;

import java.util.Random;

public class Source {

    private Random r = new Random();
    private final double lam;
    private double time = 0;
    private Integer refuse = 0;
    private Integer requestCounter = 0;
    private double waitTime = 0;
    private double timeInSystem = 0;
    private double processingTime = 0;

    private int id;

    public Source (double sourceLam, int id)
    {
        refuse = 0;
        this.id = id;
        lam = sourceLam;
        time = 0;
    }


    public Request GenNew(){
        requestCounter++;
        time = time + -1 /(lam) * (Math.log(r.nextDouble()));
        return new Request(id, time, requestCounter);
    }


    public double getTime() {
        return time;
    }

    public Integer getRefuse() {
        return refuse;
    }

    public void incRefuse() {
        refuse++;
    }

    public int getId() {
        return id;
    }

    public Integer getRequestCounter() {
        return requestCounter;
    }

    public double getWaitTime() {
        return waitTime;
    }

    public void incWaitTime(double waitTime) {
        this.waitTime += waitTime;
    }

    public double getTimeInSystem() {
        return timeInSystem;
    }

    public void incTimeInSystem(double timeInSystem) {
        this.timeInSystem += timeInSystem;
    }

    public void incProcessingTime(double time) {
        this.processingTime += time;
    }

    public double getProcessingTime() {
        return processingTime;
    }
}
