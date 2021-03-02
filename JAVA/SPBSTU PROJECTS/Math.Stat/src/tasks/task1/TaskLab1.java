package tasks.task1;

import java.util.ArrayList;
import tasks.Tasks;

public class TaskLab1 implements Tasks{
    @Override
    public void run() {
        task1();
    }


    public static void task1(){
        int n = 10000;
        final ArrayList<Double> list = ToolsLab1.randomList(n);
        System.out.println(ToolsLab1.matOz(list));
        System.out.println(ToolsLab1.dispersion(list));

        //ToolsLab1.listToFile(ToolsLab1.autocorrelation(list), "file.txt");
        //ToolsLab1.listToFile(ToolsLab1.plotnRaspr(list, 12), "file.txt");
        //ToolsLab1.listToFile(ToolsLab1.fRaspr(list, 12), "file.txt");
    }
}
