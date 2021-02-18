package task2;

import task1.ToolsLab1;
import java.util.ArrayList;

public class ToolsLab2 {

    public static double gaussrand(double mo, double sko){
        double sum = 0.0;
        double x;
        for (int i = 0; i < 28; i++){
            sum += Math.random();
        }
        return (Math.sqrt(2.0) * sko * (sum - 14.)) / 2.11233 + mo;
    }

    public static int rnnorm(int n, double p){
        if (n>=100){
            return (int)Math.round(gaussrand(n * p, Math.sqrt(n * p * (1.0 -p))) + 0.5);
        } else {
            double a = Math.random();
            double temp = Math.pow(1 - p, n);
            int m = 0;
            while (a - temp >= 0){
                a -= temp;
                temp *= ((p*(n - m)) / ((m+1) * (1 - p)));
                m++;
            }
            return m;
        }
    }

    public static int irngeo1(double p){
        double a = Math.random();
        double temp = p;
        int m = 0;
        while (a - temp >= 0){
            a -= temp;
            temp *= (1 - p);
            m++;
        }
        return m;
    }

    public static int irngeo2(double p){
        double a = Math.random();
        int m = 0;
        while (a > p){
            a = Math.random();;
            m++;
        }
        return m;
    }

    public static int irngeo3(double p){
        double a = Math.random();
        return (int)Math.round(Math.log(a) / Math.log(1 - p)) + 1;
    }

    public static int irnpoi(double mu){
        if (mu < 88){
            double a = Math.random();
            double temp = Math.exp(-mu);
            int m = 1;
            while (a - temp >= 0){
                a -= temp;
                temp *= mu / m;
                m++;
            }
            return m;
        } else {
            return (int)Math.round(gaussrand(mu, mu));
        }
    }

    public static int irnpsn(double mu){
        if (mu < 88){
            double a = Math.random();
            double temp = a;
            int m = 1;
            while (temp >= Math.exp(-mu)){
                a = Math.random();
                temp *= a;
                m++;
            }
            return m;
        } else {
            return (int)Math.round(gaussrand(mu, mu));
        }
    }

    public static int irnlog(double q){
        double a = Math.random();
        double temp = -(1.0 / Math.log(q)) * (1 - q);
        int m = 1;
        while (a - temp >= 0){
            a -= temp;
            temp *= (m * 1.0 / (m + 1)) * (1 - q);
            m++;
        }
        return m;
    }


    public static int irnuni(int iLow, int iUp){
        return iLow - 1 + (int) (Math.random() * iUp + 1);
    }

    public static int binom(int iLow, int iUp){
        return iLow - 1 + (int) (Math.random() * iUp + 1);
    }

    public static void check(int iLow, int iUp, int n){
        ArrayList<Double> list = new ArrayList<>();

        for (int i = 0; i < n; i++){
            //list.add((double) irnuni(iLow, iUp));
            //list.add((double) rnnorm(10, 0.5));
            //list.add((double) irngeo3(0.5));
            //list.add((double) irnpoi(10.0));
            //list.add((double) irnpsn(10.0));
            list.add((double) irnlog(0.5));
        }

        System.out.println(ToolsLab1.matOz(list));
        System.out.println(ToolsLab1.dispersion(list));

        //ToolsLab1.listToFile(ToolsLab1.plotnRaspr(list, 12));
        ToolsLab1.listToFile(ToolsLab1.fRaspr(list, 12));
    }

}
