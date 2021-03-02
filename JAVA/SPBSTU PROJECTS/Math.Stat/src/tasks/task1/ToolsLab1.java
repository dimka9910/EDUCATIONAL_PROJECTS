package tasks.task1;

import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;

public class ToolsLab1 {

    public static ArrayList<Double> plotnRaspr(ArrayList<Double> list, int n){
        Collections.sort(list);
        ArrayList<Double> result = new ArrayList<>();
        for (int i = 0; i < n; i++){
            result.add(0.0);
        }

        double step = (list.get(list.size() - 1) - list.get(0))/ n;
        for (int i = 0; i < n; i++){
            for (double d: list){
                if (d >= step * i){
                    if (d >= step * (i + 1)){
                        break;
                    }
                    result.set(i, result.get(i) + 1);
                }
            }
        }

        for (int i = 0; i < n; i++){
            result.set(i, result.get(i)/list.size());
        }
        return result;
    }

    public static ArrayList<Double> fRaspr(ArrayList<Double> list, int n){
        ArrayList<Double> result = plotnRaspr(list, n);
        double sum = 0;
        for (int i = 0; i < result.size(); i++){
            result.set(i, result.get(i) + sum);
            sum = result.get(i);
        }
        return result;
    }



    public static ArrayList<Double> randomList(int n) {
        ArrayList<Double> list = new ArrayList<>();
        for (int i = 0; i < n; i++){
            list.add(Math.random());
        }
        return list;
    }

    public static double matOz(ArrayList<Double> list){
        double sum = 0;
        for(double d: list){
            sum = sum + d;
        }
        return sum / list.size();
    }

    public static double dispersion(ArrayList<Double> list){
        double tmp = 0;
        double _M = matOz(list);
        for(double d: list){
            tmp += (d - _M) * (d - _M);
        }
        return tmp / list.size();
    }

    public static double otklon(ArrayList<Double> list){
        return Math.sqrt(dispersion(list));
    }

    public static ArrayList<Double> autocorrelation(ArrayList<Double> list){
     ArrayList<Double> listAutocor = new ArrayList<>();
     double temp = dispersion(list) * list.size();
     double _M = matOz(list);

     for (int f = 0; f < list.size(); f++){
         double sum = 0;
         for (int i = 0; i < list.size() - f; i++){
             sum += (list.get(i) - _M) * (list.get(i + f) - _M);
         }
         listAutocor.add(sum / temp);
     }
     return listAutocor;
    }

    public static void listToFile(ArrayList<Double> list, String str){
        File file = new File(str);
        try {
            FileWriter writer = new FileWriter(file, false); // overwrites the file
            for (double d : list){
                writer.write(String.valueOf(d) + "\n");
            }
            writer.close();
        } catch (Exception ignored){
        }
    }
}
