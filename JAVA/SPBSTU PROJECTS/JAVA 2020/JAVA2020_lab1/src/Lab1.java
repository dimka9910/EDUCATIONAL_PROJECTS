import java.util.Scanner;

public class Lab1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        double a = in.nextDouble();
        double b = in.nextDouble();
        boolean flag = false;
        if (b < a)
        {
            double bb = b;
            b = a;
            a = bb;
        }

        System.out.printf("Промежуток: [%f; %f] \n", a, b);
        System.out.println("Простые числа:");


        for (int i = (int)a; i < b; i++)
        {
            for (int j = 2; j < Math.abs(i); j ++)
            {
                if ( i % j == 0)
                {
                    flag = true;
                    break;
                }
            }
            if (flag == false && i != 0)
            {
                System.out.print(i + " ");
            }
            flag = false;
        }

    }

}
