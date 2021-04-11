package com.company.searching;

import java.util.List;

public class BinarySearch<T extends Comparable<T>> implements SearchMethod<T> {
    @Override
    public int search(List<T> list, T target) {
        int left = 0;
        int right = list.size() - 1;

        while (left <= right){
            int mid = (left + right) >>> 1;
            if (target.equals(list.get(mid)))
                return mid;
            if (target.compareTo(list.get(mid)) < 0){
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
}
