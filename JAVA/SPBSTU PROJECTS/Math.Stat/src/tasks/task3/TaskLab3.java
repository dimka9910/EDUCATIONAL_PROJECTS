package tasks.task3;

import tasks.Tasks;
import tasks.task1.ToolsLab1;

import java.util.ArrayList;

public class TaskLab3 implements Tasks {
    @Override
    public void run() {
        ArrayList<Double> list = new ArrayList<>();
        for (int i = 0; i < 10000; i++){
            double d;
//            d = ToolsLab3.rnuni(1,100);
//            d = ToolsLab3.rnnrm1();
//            d = ToolsLab3.rnnrm2();
//            d = ToolsLab3.rnexp(1);
//            d = ToolsLab3.rnchis();
            d = ToolsLab3.rnstud();
            list.add(d);
        }

        System.out.println(ToolsLab1.matOz(list));
        System.out.println(ToolsLab1.dispersion(list));

        ToolsLab1.listToFile(ToolsLab1.plotnRaspr(list, 12), "file1.txt");
        ToolsLab1.listToFile(ToolsLab1.fRaspr(list, 12), "file2.txt");
    }
}
