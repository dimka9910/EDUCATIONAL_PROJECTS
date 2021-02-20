package task2;

import task1.ToolsLab1;

import java.util.Scanner;

public class TaskLab2 {
    public static void task2() {
        boolean flag = true;
        while (flag == true) {
            ToolsLab2 toolsLab2 = new ToolsLab2();

            Scanner scanner = new Scanner(System.in);
            System.out.println("Введите номер необходимого датчика:" +
                    "\n 1) irnuni" +
                    "\n 2) rnnorm" +
                    "\n 3) irngeo1" +
                    "\n 4) irngeo2" +
                    "\n 5) irngeo3" +
                    "\n 6) irnpoi" +
                    "\n 7) irnpsn" +
                    "\n 8) irnlog\n");

            double a = 0;
            double b = 0;
            int n = 10000;
            int num = 0;

            try {
                num = scanner.nextInt();
            } catch (Exception ignored){ }

            switch (num) {
                case 1:
                    toolsLab2.setMethod(new irnuni());
                    a = 1;
                    b = 100;
                    break;
                case 2:
                    toolsLab2.setMethod(new rnnorm());
                    a = 10;
                    b = 0.5;
                    break;
                case 3:
                    toolsLab2.setMethod(new irngeo1());
                    a = 0.5;
                    break;
                case 4:
                    toolsLab2.setMethod(new irngeo2());
                    a = 0.5;
                    break;
                case 5:
                    toolsLab2.setMethod(new irngeo3());
                    a = 0.5;
                    break;
                case 6:
                    toolsLab2.setMethod(new irnpoi());
                    a = 10.0;
                    break;
                case 7:
                    toolsLab2.setMethod(new irnpsn());
                    a = 10.0;
                    break;
                case 8:
                    toolsLab2.setMethod(new irnlog());
                    a = 0.5;
                    break;
                default:
                    flag = false;
                    break;
            }

            if (flag)
                toolsLab2.check(a, b, n);
        }
    }
}
