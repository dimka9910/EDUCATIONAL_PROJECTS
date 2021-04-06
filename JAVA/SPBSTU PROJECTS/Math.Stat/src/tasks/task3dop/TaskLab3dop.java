package tasks.task3dop;

import tasks.Tasks;
import tasks.task1.ToolsLab1;

import java.util.ArrayList;
import java.util.Collections;

public class TaskLab3dop implements Tasks {
    @Override
    public void run() {
        ArrayList<Double> list = new ArrayList<>();
        for (int i = 0; i < 100; i++){
            double d;
            d = ToolsLab3dop.normalDistributionWithParameters(4, 0.5); //нормальное
            list.add(d);
        }

        ToolsLab1.listToFile(list, "file1.txt");
    }
}
