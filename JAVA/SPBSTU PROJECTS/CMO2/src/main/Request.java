package main;
import java.util.Random;

public class Request {

    private Random r = new Random();
    private double time;
    private Integer refuse = 0;
    private Integer requestCounter = 0;
    private int id;
    private double waitTime = 0;
    private double startTime = 0;
    private double endTime = 0;
    private int id_source;

    public Request (int id, double time, int requestCounter)
    {
        this.id = (id+1)*100000+requestCounter;
        this.id_source = id;
        this.time = time;
        startTime = time;
    }
    
    public double getTime() {
        return time;
    }
    

    public int getId() {
        return id;
    }
    

    public double getWaitTime() {
        return waitTime;
    }

    public void setWaitTime(double waitTime) {
        this.waitTime = waitTime;
    }

    public double getStartTime() {
        return startTime;
    }

    public void setStartTime(double startTime) {
        this.startTime = startTime;
    }


    public int getId_source() {
        return id_source;
    }


    public void setEndTime(double endTime) {
        this.endTime = endTime;
    }

    public double getEndTime() {
        return endTime;
    }
}
