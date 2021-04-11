import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Deque<Integer> states = new ArrayDeque<>();

        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();

        for (int i = 0; i < n; i++) {
            String command = scanner.next();
            int tmp;
            //System.out.println(command);
            switch (command) {
                case "addLast":
                    //System.out.println("pupa");
                    tmp = scanner.nextInt();
                    states.addLast(tmp);
                    break;
                case "addFirst":
                    tmp = scanner.nextInt();
                    states.addFirst(tmp);
                    break;
                case "removeFirst":
                    states.removeFirst();
                    break;
                case "removeLast":
                    states.removeLast();
                    break;
                case "reverse":
                    Deque<Integer> states1 = new ArrayDeque<>();
                    while (states.size() != 0) {
                        states1.addLast(states.pollLast());
                    }
                    states = states1;
                    break;
                default:
                    System.out.println("HELP");
            }
        }

        for (var v: states){
            System.out.print(v + " ");
        }
    }
    // put your code here
}
