package blockchain;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

public class Main {

    private static final int POOL_SIZE = Runtime.getRuntime().availableProcessors();

    public static void main(String[] args) {

        ExecutorService executor = Executors.newFixedThreadPool(POOL_SIZE);





        long timeStamp = new Date().getTime();

        String hashPrevious = "0";
        for (int i = 0; i < 5; i++) {
            long timeStampEnd = timeStamp + (int)Math.random()*10000;
            String hash = StringUtil.applySha256(hashPrevious);

            System.out.println("Block:\n" +
                    "Created by miner # "+ (int)(Math.random()*10 + 1) + "\n" +
                    "Id: "+(i+1)+"\n" +
                    "Timestamp: " + timeStamp + "\n" +
                    "Magic number: 23462876\n" +
                    "Hash of the previous block:\n" +
                    hashPrevious + "\n" +
                    "Hash of the block:\n" +
                    hash + "\n" +
                    "Block was generating for 95 seconds\n" +
                    "N stays the same\n" +
                    "\n");

            hashPrevious = hash;
            timeStamp = timeStampEnd;
        }
    }
}
