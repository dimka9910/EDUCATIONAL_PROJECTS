package com.company.sorting;

import java.util.List;

public interface SortMethod<T extends Comparable<T>> {
    void sort(List<T> list);

    default void swap(List<T> list, int a, int b){
        T tmp = list.get(a);
        list.set(a, list.get(b));
        list.set(b, tmp);
    }
}
