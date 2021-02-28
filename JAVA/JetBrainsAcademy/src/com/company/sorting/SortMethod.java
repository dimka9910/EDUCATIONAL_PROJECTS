package com.company.sorting;

import java.util.List;

public interface SortMethod<T extends Comparable<T>> {
    void sort(List<T> list);
}
