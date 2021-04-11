package blockchain;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Blockchain {
    LinkedList<Block> list;

    public Blockchain(int n) {
        list = new LinkedList<>();
        list.add(new Block(1, "0"));
    }

    public void generate(){
        Block block = new Block(list.getLast());
        double magicNumber = Math.random();

        list.add(new Block(list.getLast()));
    }

    private void generateHash(){
//        do {
//            magicNumber = Math.random();
//            currentHash = StringUtil.applySha256(getAllFields());
//        } while (!currentHash.substring(0, zerosAmount).equals(createZerosString()));
    }


    public LinkedList<Block> getList() {
        return list;
    }
}
