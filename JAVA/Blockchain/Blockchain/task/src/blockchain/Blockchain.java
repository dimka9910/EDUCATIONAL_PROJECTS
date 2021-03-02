package blockchain;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Blockchain {
    LinkedList<Block> list;

    public Blockchain(int n) {
        list = new LinkedList<>();
        list.add(new Block(1, "0", n));
    }

    public void generate(){
        list.add(new Block(list.getLast()));
    }


    public LinkedList<Block> getList() {
        return list;
    }
}
