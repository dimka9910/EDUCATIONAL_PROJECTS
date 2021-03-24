package tasks.task3;

import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.IntStream;

public class ToolsLab3 {
    public static double rnuni(double a, double b){
        return Math.random() *(b - a) + a;
    }

    public static double rnnrm1(){
        return Math.sqrt(-2 * Math.log(Math.random()))
                * Math.cos(2 * Math.PI * Math.random());
    }

    public static double rnnrm2(){
        double r = 0.0;
        for (int i = 0; i < 12; i++)
            r += Math.random();
        return r - 6;
    }

    public static double rnexp(double b){
        return -b * Math.log(Math.random());
    }

    public static double rnchis(){
        double yn = 0.0;
        for (int i = 0; i < 10; i++){
            double z = rnnrm1();
            yn += z * z;
        }
        return yn;
    }

    public static double rnstud(){
        return rnnrm1() / Math.sqrt(rnchis()/10.0);
    }
}
