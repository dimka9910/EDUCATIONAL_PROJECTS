package tasks.task3dop;

import tasks.task3.ToolsLab3;

public class ToolsLab3dop {
    public static double normalDistributionWithParameters(double m, double dispersion){
        return ToolsLab3.rnnrm1() * Math.sqrt(dispersion) + m;
    }
}
