package com.company.searching;

import java.util.List;

public class JumpSearch<T extends Comparable<T>> implements SearchMethod<T> {
    @Override
    public int search(List<T> list, T target) {
        int step = (int) Math.sqrt(list.size() - 1);
        int left = 0;
        int right = 0;

        int tmp = list.size() % step;
        if (tmp != 0 && target.compareTo(list.get(list.size() - 1)) <= 0
                && target.compareTo(list.get(list.size() - tmp)) >= 0) {
            left = list.size() - tmp;
            right = list.size() - 1;
        } else {
            for (int i = 0; i < list.size(); left = i, i += step)
                if (target.compareTo(list.get(i)) <= 0) {
                    right = i;
                    break;
                }
        }
        return backwardSearch(list, target, left, right);
    }

    private int backwardSearch(List<T> list, T target, int leftExcl, int rightIncl) {
        for (int i = rightIncl; i >= leftExcl; i--) {
            if (list.get(i).equals(target)) {
                return i;
            }
        }
        return -1;
    }

}
