package com.company.collections;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class TheList implements CollectionApp {
    public static void main(String[] args) {
        CollectionApp cp = new TheList();
        cp.run();
    }

    @Override
    public void run() {
        /**     --------------      */
        /**     IMMUTABLE LIST      */
        /**     --------------      */
        String kenny = "Kenny";

        List<String> emptyList = List.of(); // 0 elements
        List<String> names = List.of("Larry", "Kenny", "Sabrina");          // 3 elements
        List<Integer> immutableNumbers = List.of(0, 1, 1, 2, 3, 5, 8, 13);  // 8 elements

        System.out.println(emptyList.indexOf("hello"));                     // -1
        System.out.println(names.indexOf(kenny));                           // 1
        System.out.println(immutableNumbers.lastIndexOf(1));             // 2

        System.out.println(immutableNumbers.subList(2, 5));                 // [1, 2, 3]

        try { //  throws  UnsupportedOperationException
            names.set(0, "Funday");
            names.add("Holiday");
        } catch (UnsupportedOperationException ignored) {
        }

        /**     --------------      */
        /**       MUTABLE LIST      */
        /**     --------------      */

        List<Integer> numbers = new ArrayList<>();

        numbers.add(15);
        numbers.add(10);
        numbers.add(20);

        System.out.println(numbers);  //  [15,  10,  20]
        numbers.set(0, 30);           //  no exceptions  here
        System.out.println(numbers);  //  [30,  10,  20]

        List<String> immutableList1 = Arrays.asList("Larry", "Kenny", "Sabrina");
        List<String> immutableList2 = List.of("Larry", "Kenny", "Sabrina");
        List<String> mutableList1 = new ArrayList<>(immutableList1);
        List<String> mutableList2 = new ArrayList<>(immutableList2);
        System.out.println(mutableList1);
        System.out.println(mutableList2);

        System.out.println(Objects.equals(immutableList1, immutableList2)); // TRUE
        System.out.println(Objects.equals(immutableList1, mutableList2));   // TRUE
        System.out.println(Objects.equals(names, mutableList2));            // TRUE

        Objects.equals(List.of(1, 2, 3), List.of(1, 2, 3));            //  true
        Objects.equals(List.of(1, 2, 3), List.of(1, 3, 2));            //  false
        Objects.equals(List.of(1, 2, 3), List.of(1, 2, 3, 1));         //  false
    }
}
