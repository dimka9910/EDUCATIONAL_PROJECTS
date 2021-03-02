package tasks.task1;
import tasks.Tasks;
import java.util.ArrayList;

public class TaskLab1_dop implements Tasks {
    @Override
    public void run() {
        for (int i = 0; i++ < 10;) task();
    }

    public static ArrayList<Double> fractionOfOnes(ArrayList<Integer> list, int N) {

        ArrayList<Double> p = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            p.add(0.0);
        }

        int M = (list.size()) / N;
        for (int i = 0; i < N; i++)
            for (int j = i * M; j < (i + 1) * M; j++)
                if (list.get(j) == 1)
                    p.set(i, p.get(i) + 1);

        for (int i = 0; i < N; i++) {
            p.set(i, p.get(i) / M);
        }

        double hiKvadrat = 0.0;
        for (var pi: p){
            hiKvadrat += (pi - 0.5) * (pi - 0.5);
        }

        hiKvadrat = hiKvadrat * 4 * M;
        System.out.println(hiKvadrat);
        return p;
    }

    public void task() {
        ArrayList<Integer> list = new ArrayList<>();
        for (int i = 0; i++ < 100000; )
            list.add((int) (Math.random() * (2)));

        fractionOfOnes(list, 20);
    }
}
