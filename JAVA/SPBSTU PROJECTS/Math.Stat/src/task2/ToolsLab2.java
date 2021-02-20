package task2;

import task1.ToolsLab1;
import java.util.ArrayList;

public class ToolsLab2 {

    private GeneratingMethod method;

    public void setMethod(GeneratingMethod method) {
        this.method = method;
    }

    public void check(double a, double b, int n){
        ArrayList<Double> list = new ArrayList<>();

        for (int i = 0; i < n; i++){
            list.add((double) method.generate(a,b));
        }

        // Методы из пакета лабораторной №1
        System.out.println(ToolsLab1.matOz(list));
        System.out.println(ToolsLab1.dispersion(list));

        ToolsLab1.listToFile(ToolsLab1.plotnRaspr(list, 12), "file1.txt");
        ToolsLab1.listToFile(ToolsLab1.fRaspr(list, 12), "file2.txt");
    }

}
