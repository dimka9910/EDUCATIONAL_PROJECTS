package tictactoe;

import java.util.Scanner;

public class Main {

    private static boolean winX;
    private static boolean winO;
    private static Scanner scanner = new Scanner(System.in);
    private static char [] arrayChars;

    public static int count(String str, String target) {
        return (str.length() - str.replace(target, "").length()) / target.length();
    }


    public static void comp (int a, int b) {
        int i = a;
        if (arrayChars[i] == arrayChars[i + b] && arrayChars[i] == arrayChars[i + 2*b]){
            if (arrayChars[i] == 'X'){
                winX = true;
            }
            if (arrayChars[i] == 'O'){
                winO = true;
            }
        }
    }

    public static void print (char [] arrayChars) {
        System.out.println("---------");
        for(int i = 0; i < arrayChars.length; i++){
            if ( i % 3 == 0)
                System.out.print("| ");
            System.out.print(arrayChars[i] + " ");
            if ( i % 3 == 2)
                System.out.print("|\n");
        }
        System.out.println("---------");
    }

    public static String checkGame(){
        winX = false;
        winO = false;
        String str = new String(arrayChars);
        comp(0, 1);
        comp( 3, 1);
        comp( 6, 1);

        comp( 0, 3);
        comp( 1, 3);
        comp( 2, 3);

        comp( 0, 4);
        comp( 2, 2);

        if (Math.abs(count(str, "X") - count(str, "O")) > 1 ||
                (winX && winO == true)){
            //return "Impossible";
        }  else if (winX == true) {
            return  "X wins";
        } else if (winO == true) {
            return  "O wins";
        } else if ( count(str, "_") == 0) {
            return "Draw";
        } else {
            //System.out.println("Game not finished");
        }
        return "non";
    }

    public static void enterCoordinates(char c){
        System.out.print("Enter the coordinates: ");
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        if (x > 3 || x < 1 || y > 3 || y < 0){
            System.out.println("Coordinates should be from 1 to 3!");
            enterCoordinates(c);
            return;
        }
        if (arrayChars[(x-1)*3 + y - 1] != '_'){
            System.out.println("This cell is occupied! Choose another one!");
            enterCoordinates(c);
            return;
        }
        arrayChars[(x-1)*3 + y - 1] = c;
        print(arrayChars);
    }

    public static void main(String[] args) {

        String str = "_________";
        arrayChars = str.toCharArray();
        print(arrayChars);

        while (true){
            enterCoordinates('X');
            if (checkGame() != "non")
                break;
            enterCoordinates('O');
            if (checkGame() != "non")
                break;
        }

        System.out.println(checkGame());

    }
}
