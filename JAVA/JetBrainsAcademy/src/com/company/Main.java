package com.company;

import com.company.sorting.BubbleSort;
import com.company.sorting.SortMethod;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        int i = 0;
        while (i++<100){
            list.add((int)(Math.random() * 200));
        }

        SortMethod<Integer> sort = new BubbleSort<Integer>();
        sort.sort(list);

        for (var v: list){
            System.out.println(v);
        }

    }
}
