package com.company.mainFiles;

import com.company.sorting.InsertionSort;
import com.company.sorting.SortMethod;

import java.util.ArrayList;
import java.util.List;

public class mainSort {

    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        int i = 0;
        while (i++<101){
            list.add((int)(Math.random() * 20000));
        }

        SortMethod<Integer> sort = new InsertionSort<>();

        sort.sort(list);

        list.forEach(System.out::println);
    }
}
