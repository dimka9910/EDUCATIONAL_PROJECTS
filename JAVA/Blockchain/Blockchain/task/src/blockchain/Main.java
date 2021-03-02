package blockchain;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.util.stream.IntStream;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter how many zeros the hash must start with: ");
        int n = scanner.nextInt();
        System.out.println();

        Blockchain blockchain = new Blockchain(n);
        for (int i = 2; i < 6; i++) {
            blockchain.generate();
        }

        blockchain.getList().forEach(System.out::println);
    }
}
