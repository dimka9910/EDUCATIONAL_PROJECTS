package tasks.task4;

import tasks.Tasks;

import java.util.*;

class Element{
    int typeOfElement;
    double time;
    double lambda;

    public Element(int typeOfElement) {
        this.typeOfElement = typeOfElement;
        this.time = 0;
        this.lambda = 0;
    }

    public void incTime(){ time = time - Math.log(Math.random()) / lambda; }
    public void setTime(){ time = - Math.log(Math.random()) / lambda; }
    public double getTime() { return time; }
}

public class TaskLab4 implements Tasks {

    private final int N;

    public TaskLab4() {
        double p = 0.99;
        double epsilon = 1e-3;
        double Ta = 2.32;
        N = (int)(Ta * Ta * p * (1-p) / (epsilon*epsilon));
        System.out.println(N);
    }

    boolean check(Element[] x){
        double t = 8760;
        return (((x[0].time > t) || (x[1].time > t)) && (x[2].time > t) &
                (x[3].time > t) && (x[4].time > t) &&
                ((x[5].time > t) || (x[6].time > t) || (x[7].time > t)));
    }

    public double simulation(int[] spareParts){
        //final int N = 53562;
        int size = 8;
        int typeOfElementAmount = 3;
        int breakdownCounter = 0;
        Element[] x = new Element[size];
        x[0] = new Element(0);
        x[1] = new Element(0);
        x[2] = new Element(1);
        x[3] = new Element(1);
        x[4] = new Element(1);
        x[5] = new Element(2);
        x[6] = new Element(2);
        x[7] = new Element(2);
        double[] lambda = {40.0e-6, 10.0e-6, 80.0e-6};
        for (int i = 0; i < size; i++)
            x[i].lambda = lambda[x[i].typeOfElement];

        for (int iteration = 0; iteration < N; iteration++) {
            Arrays.stream(x).forEach(Element::setTime);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < spareParts[i]; j++) {
                    int finalI = i;
                    Arrays.stream(x)
                            .filter(element -> element.typeOfElement == finalI)
                            .min(Comparator.comparing(Element::getTime))
                            .orElseThrow(NoSuchFieldError::new).incTime();
                }
            }
            if (!check(x)) breakdownCounter++;
        }
        return 1.0 - (double)breakdownCounter/N;
    }

    @Override
    public void run() {
        List<String> list = new ArrayList<>();
        for (int part0 = 0; part0 < 5; part0++)
            for (int part1 = 0; part1 < 5; part1++)
                for (int part2 = 0; part2 < 5; part2++){
                    int[] spareParts = {part0, part1, part2};
                    double result = simulation(spareParts);
                    if (result > 0.99)
                        list.add(result + " " + Arrays.toString(spareParts));
                }
        Collections.sort(list);
        list.forEach(System.out::println);
    }
}
