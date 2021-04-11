package com.company.searching;

import java.util.List;

public interface SearchMethod<T extends Comparable<T>> {
    int search(List<T> list, T target);
}
