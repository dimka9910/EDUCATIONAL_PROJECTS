package com.company.collections;

import java.util.*;

public class TheSet implements CollectionApp {

    public static void main(String[] args) {
        CollectionApp cp = new TheSet();
        cp.run();
    }

    @Override
    public void run() {

        /**************************************************************************************************************/
        /**     --------------      */
        /**     IMMUTABLE LIST      */
        /**     --------------      */
        System.out.println("\n---- IMMUTABLE LIST ----\n");

        Set<String> emptySet = Set.of();
        Set<String> persons = Set.of("Larry", "Kenny", "Sabrina");
        Set<Integer> numbers = Set.of(100, 200, 300, 400);

        System.out.println(emptySet); // []
        System.out.println(persons);  // [Kenny, Larry, Sabrina] or another order
        System.out.println(numbers);  // [400, 200, 300, 100] or another order

        /**
         * For immutable sets, it's only possible to invoke
         * - contains()
         * - size()
         * - isEmpty()
         * All others will throw UnsupportedOperationException since they try to change the set.
         * If you'd like to add/remove elements, use one of HashSet, TreeSet or LinkedHashSet.
         */
        System.out.println(emptySet.contains("hello"));  // false
        System.out.println(emptySet.isEmpty());          // true
        System.out.println(persons.contains("Sabrina")); // true
        System.out.println(persons.contains("John"));    // false
        System.out.println(numbers.contains(300));       // true


        /**************************************************************************************************************/
        /**     --------------      */
        /**         HashSet         */
        /**     --------------      */
        System.out.println("\n---- HashSet ----\n");

        // default initial capacity (16) and load factor (0.75).

        // new HashSet<>()
        Set<String> countries = new HashSet<>(List.of("India", "Japan"));
        // new HashSet(int initialCapacity, float loadFactor)
        countries.add("Switzerland");
        countries.add("Japan");
        countries.add("Brazil");

        System.out.println(countries); // [Japan, Brazil, Switzerland, India]
        System.out.println(countries.contains("Switzerland")); // true


        /**************************************************************************************************************/
        /**     --------------      */
        /**         TreeSet         */
        /**     --------------      */
        System.out.println("\n---- TreeSet ----\n");

        SortedSet<Integer> sortedSet = new TreeSet<>(List.of(10, 15, 13));
        System.out.println(sortedSet.comparator()); //null because natural order

        sortedSet.add(21);
        sortedSet.add(17);

        System.out.println(sortedSet); // [10, 13, 15, 17, 21]

        System.out.println(sortedSet.headSet(15)); // [10, 13]
        // returns a subset containing elements that are strictly less than
        System.out.println(sortedSet.tailSet(15)); // [15, 17, 21]
        // returns a subset containing elements that are greater than or equal to fromElement;

        System.out.println(sortedSet.subSet(13, 17)); // [13, 15]
        // returns a subset containing elements in the range fromElement (inclusive) toElement (exclusive)

        System.out.println(sortedSet.first()); // minimum is 10
        System.out.println(sortedSet.last());  // maximum is 21

        /** Note, HashSet is much faster than TreeSet:
         * constant-time versus log-time for most operations,
         * it offers no ordering guarantees.
         * If you need to use the operations from the SortedSet interface,
         * or if the value-ordered iteration is required,
         * use TreeSet, otherwise, HashSet would be a better choice.
         */

        /**************************************************************************************************************/
        /**     --------------      */
        /**     LinkedHashSet       */
        /**     --------------      */
        System.out.println("\n---- LinkedHashSet ----\n");

        Set<Character> characters = new LinkedHashSet<>();

        for (char c = 'a'; c <= 'k'; c++) {
            characters.add(c);
        }
        System.out.println(characters); // [a, b, c, d, e, f, g, h, i, j, k]

        /** More memory then HashSet but as fast as Hash set
         * No sorting but saves order of elements
         * smthg intermediate between HashSet and TreeSet
         */

        /**************************************************************************************************************/
        /**     --------------      */
        /**     Set operations      */
        /**     --------------      */

        System.out.println("\n---- Set operations ----\n");

        /** getting a mutable set from an immutable one */
        countries = new HashSet<>(List.of("India", "Japan", "Switzerland"));

        /** @addAll - UNION */
        countries.addAll(List.of("India", "Germany", "Algeria"));
        System.out.println(countries);
        // [Japan, Algeria, Switzerland, Germany, India]

        /** @retainAll - INTERSECTION */
        countries.retainAll(List.of("Italy", "Japan", "India", "Germany"));
        System.out.println(countries);
        // [Japan, Germany, India]

        /** @removeAll - DIFFERENCE */
        countries.removeAll(List.of("Japan", "Germany", "USA"));
        System.out.println(countries);
        // [India]

        countries = new HashSet<>(List.of("India", "Japan", "Algeria"));

        System.out.println(countries.contains("India"));                                    // true
        System.out.println(countries.containsAll(Set.of()));                                // true
        System.out.println(countries.containsAll(Set.of("India", "Japan")));                // true
        System.out.println(countries.containsAll(Set.of("India", "Germany")));              // false
        System.out.println(countries.containsAll(Set.of("Algeria", "India", "Japan")));     // true

        Objects.equals(Set.of(1, 2, 3), Set.of(1, 3));    // false
        Objects.equals(Set.of(1, 2, 3), Set.of(1, 2, 3)); // true
        Objects.equals(Set.of(1, 2, 3), Set.of(1, 3, 2)); // true

        numbers = new HashSet<Integer>(Set.of(1, 2, 3));
        Objects.equals(numbers, Set.of(1, 2, 3)); // true

    }
}
