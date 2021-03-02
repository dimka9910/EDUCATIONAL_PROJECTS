package blockchain;

import java.util.Date;
import java.util.stream.IntStream;

public class Block {
    private int id;
    private String currentHash;
    private String previousHash;
    private long timeStamp;
    private long timeStampGenerated;
    private int zerosAmount;
    private String hashZeros;
    private double magicNumber;

    public Block(Block previousBlock) {
        timeStamp = new Date().getTime();
        this.id = previousBlock.getId() + 1;
        this.previousHash = previousBlock.getCurrentHash();
        this.zerosAmount = previousBlock.zerosAmount;
        this.hashZeros = previousBlock.hashZeros;
        //currentHash = StringUtil.applySha256(getAllFields());
        generateHash();
        timeStampGenerated = new Date().getTime();
    }

    public Block(int id, String previousHash, int n) {
        hashZeros = "";
        zerosAmount = n;
        timeStamp = new Date().getTime();
        this.id = id;
        this.previousHash = previousHash;
        //currentHash = StringUtil.applySha256(getAllFields());
        IntStream.range(0,n).forEach(i -> hashZeros += "0");
        generateHash();
        timeStampGenerated = new Date().getTime();
    }

    private void generateHash(){
        do {
            magicNumber = Math.random();
            currentHash = StringUtil.applySha256(getAllFields());
        } while (!currentHash.substring(0, zerosAmount).equals(hashZeros));
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
                (int)((timeStampGenerated - timeStamp)/1000) + " seconds\n";
    }

    public String getCurrentHash() {
        return currentHash;
    }

    public int getId() {
        return id;
    }
}
