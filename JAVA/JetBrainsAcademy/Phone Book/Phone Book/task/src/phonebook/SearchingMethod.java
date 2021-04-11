package phonebook;

import javax.sound.midi.Soundbank;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.Scanner;

public class SearchingMethod {



    public static void lineralSearch(List<String> list1, List<String> list2){
        long time = System.currentTimeMillis();
        try {
            System.out.println("Start searching...");
            int i = 0;
            int j = 0;
            for (var l2: list2){
                j++;
                for (var l1: list1){
                    if (l2.equals(l1)){
                        i++;
                        break;
                    }
                }
            }
            time = System.currentTimeMillis() - time;
            String timeout = time / 60000 + " min. " + (time % 60000) / 1000
                    + " sec. " + (time % 60000) % 1000 + " ms.";
            System.out.println("Found " + i + " / " + j + " entries. Time taken: " + timeout);
        } catch (Exception e){
            return;
        }
    }

    public static List<String> bubbleSort (List<String> list, boolean asc){
        for (int i = 0; i < list.size(); i++){
            for (int j = 0; j < list.size() - 1; j++){
                if (list.get(j).compareTo(list.get(j + 1)) > 0){
                    String tmp = list.get(j);
                    list.set(j, list.get(j + 1));
                    list.set(j + 1, tmp);
                }
            }
        }
        return list;
        //int step = (int)Math.sqrt(list.size());
    }


}
