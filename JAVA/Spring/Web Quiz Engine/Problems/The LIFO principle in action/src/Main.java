import java.beans.BeanProperty;
import java.lang.annotation.Annotation;
import java.lang.reflect.Method;
import java.util.*;

//class Pupa{
//
//    static {
//        a = 10;
//    }
//
//    int a = 5;
//
//}

class Main {


    @BeanProperty
    public String toString() {
        return super.toString();
    }

    @Deprecated
    static int hash() {
        int h;
        Integer key = 0;
        return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
    }

    public static void main(String[] args) throws NoSuchMethodException {


        for (Method method : Main.class.getDeclaredMethods()) {
            for (Annotation annotation : method.getDeclaredAnnotations()) {
                System.out.print(annotation + "  -  ");
            }
        }

        Method method = Main.class.getDeclaredMethod("hash");
        method.isAnnotationPresent(Deprecated.class);
//        characters.size();
//
//        characters.put(45, "The King");
//        characters.put(46, "The King");
//        characters.put(47, "The King");

        //characters.hashCode();

////        Scanner scanner = new Scanner(System.in);
////        int n = scanner.nextInt();
////
////        Stack<Integer> stack = new Stack<>();
////
////        for (int i = 0; i < n; i++)
////            stack.add(scanner.nextInt());
////
////        for (int i = 0; i < n; i++)
////            System.out.println(stack.pop());
//        //stack.forEach(System.out::println);
//        // put your code here
//        Pupa pupa = new Pupa();
//        System.out.println(pupa.a);
    }
}
