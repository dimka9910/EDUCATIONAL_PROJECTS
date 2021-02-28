package com.company.sorting;

import java.util.List;

public class QuickSort<T extends Comparable<T>> implements SortMethod<T>{
    private int pivotIndex(List<T> list, int left, int right){
        return right;
    }

    private void quickSort(List<T> list, int left, int right){
        if (left < right){
            int pivotIndex = partition(list, left, right);
            quickSort(list, left, pivotIndex - 1);
            quickSort(list, pivotIndex + 1, right);
        }
    }

    private int partition(List<T> list, int left, int right){
        int pivotIndex = pivotIndex(list, left, right);
        T pivot = list.get(pivotIndex);
        int partitionIndex = left;

        for (int i = left; i <= right; i++){
            if (list.get(i).compareTo(pivot) <= 0){
                swap(list, i, partitionIndex);
                partitionIndex++;
            }
        }
        return partitionIndex - 1;
    }

    private void swap(List<T> list, int a, int b){
        T tmp = list.get(a);
        list.set(a, list.get(b));
        list.set(b, tmp);
    }

    @Override
    public void sort(List<T> list) {
        quickSort(list, 0, list.size() - 1);
    }
}
