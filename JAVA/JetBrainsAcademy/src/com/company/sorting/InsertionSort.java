package com.company.sorting;

import java.util.List;

public class InsertionSort<T extends Comparable<T>> implements SortMethod<T> {

    @Override
    public void sort(List<T> list) {
        for (int i = 1; i < list.size(); i++)
            for (int j = i - 1; j >= 0; j--)
                if (list.get(j + 1).compareTo(list.get(j)) < 0)
                    swap(list, j + 1, j);
                else
                    break;
    }
}
