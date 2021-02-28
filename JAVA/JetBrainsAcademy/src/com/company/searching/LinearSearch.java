package com.company.searching;

import java.util.List;

public class LinearSearch<T extends Comparable<T>> implements SearchMethod<T>{
    @Override
    public int search(List<T> list, T target) {
        for (int i = 0; i < list.size(); i++){
            if (list.get(i).equals(target))
                return i;
        }
        return -1;
    }
}
