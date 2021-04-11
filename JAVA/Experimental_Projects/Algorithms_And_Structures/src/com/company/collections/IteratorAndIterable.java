package com.company.collections;

import java.util.*;

public class IteratorAndIterable implements CollectionApp {
    public static void main(String[] args) {
        CollectionApp cp = new IteratorAndIterable();
        cp.run();
    }

    @Override
    public void run() {

        /**************************************************************************************************************/
        /**     --------------      */
        /**     Being iterable      */
        /**     --------------      */

        /**The `Collection` interface extends `Iterable`, but `Map` does not.
         Due to this, any collection class (`List`, `Queue`, `Set`) can be considered as `Iterable`.
         */
        Iterable<String> iterable = List.of("first", "second", "third");


        /**The order of elements when iterating is specific to a chosen collection.
         * For lists, the order is the same as the order of its elements.
         * */
        List<String> strings = List.of("first", "second", "third");

        // the loop prints "first", "second", and then "third"
        for (String elem : strings) {
            System.out.println(elem);
        }

        // the loop prints "first", "second", and then "third"
        strings.forEach(System.out::println);


        /**************************************************************************************************************/
        /**     --------------      */
        /**     Using iterators     */
        /**     --------------      */

        /**
         * @hasNext() - returns true if the iteration has more elements, and false otherwise;
         * @next()    - returns the next element in the iteration;
         * @remove()  - removes the last element returned by this iterator from the collection.
         */

        Set<Long> set = new TreeSet<>(Set.of(10L, 5L, 18L)); // sorted set
        set.add(14L);
        set.add(9L);

        System.out.println(set); // [5, 9, 10, 14, 18]

        // CAN BE REPLACED WITH
        /** set.removeIf(current -> current < 10L); */
        Iterator<Long> iter = set.iterator();
        while (iter.hasNext()) {
            Long current = iter.next();
            if (current < 10L) {
                iter.remove();
            }
        }

        System.out.println(set); // [10, 14, 18]

        /**************************************************************************************************************/
        /**     --------------      */
        /**  An iterator for lists  */
        /**     --------------      */
        System.out.println("\n---- An iterator for lists ----\n");

        /**
         @nextIndex() returns the index of the element that would be returned by invoking `next`;
         @hasPrevious() returns `true` if the list has more previous elements;
         @previous() returns the previous element in the list and moves the cursor position backwards;
         @previousIndex() returns the index of the element that would be returned by invoking `previous`;
         @set(E element)` replaces the last element returned by `next` or `previous` with the specified element;
         @add(E element)` inserts the specified element into the list immediately before the element
         that would be returned by `next`, and after the element that would be returned by `previous`.
         */

        List<Integer> list = new ArrayList<>(List.of(1, 2, 3, 4));
        ListIterator<Integer> iterator = list.listIterator(); // only for lists!

        System.out.println(iterator.next());     // 1
        System.out.println(iterator.next());     // 2
        System.out.println(iterator.next());     // 3
        System.out.println(iterator.previous()); // 3
        System.out.println(iterator.previous()); // 2
        iterator.add(25);
        System.out.println(list);                // [1, 25, 2, 3, 4]
        System.out.println(iterator.previous()); // 25
        System.out.println(iterator.next());     // 25
        System.out.println(iterator.next());     // 2

        iterator.set(22);
        System.out.println(list); // [1, 25, 22, 3, 4]



    }
}
