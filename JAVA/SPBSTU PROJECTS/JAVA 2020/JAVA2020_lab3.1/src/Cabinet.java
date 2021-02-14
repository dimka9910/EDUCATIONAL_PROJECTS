import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.TimeUnit;


class Cabinet //implements Runnable
{
    private int amount = 0;

    static class Student
    {
        int labsCount;
        Subj subject;
        Boolean countCheck()
        {
            return (labsCount != 0);
        }
        Student(int labsCount, Subj subject) {
            this.labsCount = labsCount;
            this.subject = subject;
        }
    }

    enum Subj{
        OOP,
        MATH,
        PHYTHICS
    }

    Queue<Student> queue_ = new LinkedList<>();

    ////////////////////////////////////////////////////////////////
    public synchronized Student get(Subj subject) {
        try
        {
            if (amount >= 8 && queue_.peek().subject == subject)
            {
                notifyAll();
                Student student = queue_.peek();
                amount--;
                System.out.println(subject + " взял на проверку: " + queue_.peek().labsCount + " лаб по предмету " + queue_.poll().subject + " В очереди теперь " + amount + " ближайший теперь " + queue_.peek().subject);
                return student;
            }
            else if (amount < 8)
            {
                System.out.println("There are no students in the cabinet");
                wait();
            }
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    ////////////////////////////////////////////////////////////////

    public synchronized void put() {
        while (amount >= 10 ) {
            try {
                wait();
            }
            catch (InterruptedException e) {
            }
        }

        amount++;
        Subj a = Subj.values()[new Random().nextInt(Subj.values().length)];

        int[] labs = new int[]{10, 20, 100};
        int n = (int)Math.floor(Math.random() * labs.length);

        queue_.add(new Student(labs[n], a));
        System.out.println("+++ Добавлен Предмет: " + a.toString() + " В очереди теперь " + amount + " ближайший в очереди " + queue_.peek().subject);
        notify(); //даёт сигнал продолжить работу
    }
}