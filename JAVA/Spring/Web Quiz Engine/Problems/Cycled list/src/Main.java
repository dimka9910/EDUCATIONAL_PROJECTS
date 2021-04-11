import java.util.*;

class Main {

    public static class Node<E> {

        private E value;
        private Node<E> next;
        private Node<E> prev;

        Node(E element, Node<E> next, Node<E> prev) {
            this.value = element;
            this.next = next;
            this.prev = prev;
        }

        Node<E> getNext() {
            return next;
        }

        Node<E> getPrev() {
            return prev;
        }

        @Override
        public int hashCode() {
            return super.hashCode();
        }
    }

    public static class DoublyLinkedList<E> {

        private Node<E> head;
        private Node<E> tail;
        private int size;

        public DoublyLinkedList() {
            size = 0;
        }

        public Node<E> getHead() {
            return head;
        }

        public Node<E> getTail() {
            return tail;
        }

        public int getSize() {
            return size;
        }

        public boolean isEmpty() {
            return size == 0;
        }

        public String toString() {
            Node<E> tmp = head;
            StringBuilder result = new StringBuilder();

            while (tmp != null) {
                result.append(tmp.value).append(" ");
                tmp = tmp.next;
            }
            return result.toString();
        }

        public void addFirst(E elem) {
            Node<E> tmp = new Node<>(elem, head, null);

            if (size == 0) {
                head = tail = tmp;
            } else {
                head.prev = tmp;
                head = tmp;
            }
            size++;
        }

        public void addLast(E elem) {
            Node<E> tmp = new Node<>(elem, null, tail);

            if (size == 0) {
                head = tail = tmp;
            } else {
                tail.next = tmp;
                tail = tmp;
            }
            size++;
        }

        public void add(E elem, Node<E> curr) {
            if (curr == null) {
                throw new NoSuchElementException();
            }
            if (curr.prev == null) {
                addFirst(elem);
                return;
            }

            Node<E> tmp = new Node<>(elem, curr, curr.prev);

            curr.prev.next = tmp;
            curr.prev = tmp;
            size++;
        }

        public void removeFirst() {
            if (size == 0) {
                throw new NoSuchElementException();
            }

            if (size == 1) {
                head = tail = null;
            } else {
                head = head.next;
                head.prev = null;
            }
            size--;
        }

        public void removeLast() {
            if (size == 0) {
                throw new NoSuchElementException();
            }

            if (size == 1) {
                head = tail = null;
            } else {
                tail = tail.prev;
                tail.next = null;
            }
            size--;
        }

        public void remove(Node<E> curr) {
            if (curr == null) {
                throw new NoSuchElementException();
            }

            if (curr.prev == null) {
                removeFirst();
                return;
            }
            if (curr.next == null) {
                removeLast();
                return;
            }

            curr.prev.next = curr.next;
            curr.next.prev = curr.prev;
            size--;
        }
    }

    public static void main(String[] args) {
        ArrayList<Integer> list = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int amount = scanner.nextInt();
        int commands = scanner.nextInt();

        int zereelement = 0;
        for(int i = 0; i < amount; i++)
            list.add(scanner.nextInt());

        for (int i = 0; i < commands; i++){
            int num;
            try {

                switch (scanner.next()){
                    case "r":
                        num = scanner.nextInt();
                        list.remove((num + zereelement) % list.size());
                        zereelement = (num + zereelement) % (list.size() + 1);
                        break;
                    case "l":
                        num = scanner.nextInt();
                        zereelement = (zereelement - num) >= 0 ? zereelement - num : list.size() + (zereelement - num) % list.size();
                        list.remove(zereelement);
                        zereelement = zereelement - 1 >= 0 ? zereelement - 1: list.size() - 1;
                        break;
                }
            } catch (Exception e){
                list.remove(0);
            }
        }

        for (var v: list){
            System.out.print(v + " ");
        }
        // put your code here
    }
}

