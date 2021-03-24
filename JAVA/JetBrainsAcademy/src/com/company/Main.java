package com.company;

import com.company.searching.BinarySearch;
import com.company.searching.JumpSearch;
import com.company.searching.SearchMethod;
import com.company.sorting.BubbleSort;
import com.company.sorting.InsertionSort;
import com.company.sorting.QuickSort;
import com.company.sorting.SortMethod;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Main {

    public static void main(String[] args) {

//        HashTable<String> table = new HashTable(5);
//
//        table.put(21, "John");
//        table.put(33, "Tom");
//        table.put(42, "Alice");
//        table.put(10, "Mike");
//        table.put(54, "Kate");
//
//        System.out.println(table);


//        Timer timer = new Timer();
//
//
        List<Integer> list = new ArrayList<>();
        int i = 0;
        while (i++<101){
            list.add((int)(Math.random() * 20000));
        }

        SortMethod<Integer> sort = new InsertionSort<>();

        sort.sort(list);

        list.forEach(System.out::println);
//
//        timer.start();
//        sort.sort(list);
//        timer.stop();
//
//        SearchMethod<Integer> searchMethod = new BinarySearch<>();
//
//        int target = list.get(100);
//        System.out.println(searchMethod.search(list, target));

//        for (var v: list){
//            //System.out.println(v);
//        }

    }
}
