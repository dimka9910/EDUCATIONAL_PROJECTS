import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Scanner;

class Node {
    public static ArrayList<Character> split(ArrayList<Character> list, int n){
        ArrayList<Character> list1 = new ArrayList<>();
        for (int i = n; i < list.size(); i++){
            list1.add(list.get(i));
        }
        for (int i = 0; i < n; i++){
            list1.add(list.get(i));
        }
        return list1;
    }

    public static ArrayList<Character> reverse(ArrayList<Character> list){
        ArrayList<Character> list1 = new ArrayList<>();
        for (int i = list.size() - 1; i >= 0; i--){
            list1.add(list.get(i));
        }
        return list1;
    }
}

class Main {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();

        ArrayList<Character> list = new ArrayList<>();
        for(var v: str.toCharArray())
            list.add(v);

        int n = scanner.nextInt();

        for (int i = 0; i < n; i++){
            String command = scanner.next();
            //System.out.println(command);
            if (command.equals("reverse"))
                list = Node.reverse(list);
            else {
                int num = scanner.nextInt();
              //  System.out.println(num);
                list = Node.split(list, num);
            }
        }

        list.forEach(System.out::print);
    }
}