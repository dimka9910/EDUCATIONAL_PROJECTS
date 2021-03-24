package blockchain;

import java.util.Date;
import java.util.stream.IntStream;

public class Block {
    private int id;
    private long timeStamp;
    private double magicNumber;
    private String previousHash;
    private String currentHash;

    public Block(Block previousBlock) {
        timeStamp = new Date().getTime();
        this.id = previousBlock.getId() + 1;
        this.previousHash = previousBlock.getCurrentHash();
    }

    public Block(int id, String previousHash) {
        timeStamp = new Date().getTime();
        this.id = id;
        this.previousHash = previousHash;
    }


    private String getAllFields(double magicN){
        return id + previousHash + timeStamp + magicN;
    }
    private String getAllFields(){
        return id + previousHash + timeStamp + magicNumber;
    }

    @Override
    public String toString() {
        return "Block:\n" +
                "Id: " + id + "\n" +
                "Timestamp: " + timeStamp + "\n" +
                "Magic number: " + (int)(magicNumber * 1000000) + "\n" +
                "Hash of the previous block: \n" +
                previousHash + "\n" +
                "Hash of the block: \n" +
                currentHash + "\n" +
                "Block was generating for " +
                (int)((new Date().getTime() - timeStamp)/1000) + " seconds\n";
    }


    public String getCurrentHash() {
        return currentHash;
    }

    public int getId() {
        return id;
    }
}
