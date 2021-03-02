import tasks.Tasks;
import tasks.task1.TaskLab1;
import tasks.task1.TaskLab1_dop;

class Main {
    public static void main(String[] args) {
        Tasks task = new TaskLab1_dop();
        task.run();
    }
}