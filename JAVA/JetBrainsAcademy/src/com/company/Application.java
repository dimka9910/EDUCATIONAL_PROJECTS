package com.company;

public class Application<T> {

    public static void main(String[] args) {

        Application<Number> application = new Application<>();
        Number n1 = application.typeBoundsTest(Integer.valueOf(10));
        Number n2 = application.typeBoundsTest(Double.valueOf(1.0));

        System.out.println(String.format("%s %s", n1, n2));

    }

    public <T1 extends Number> T1 typeBoundsTest(T1 item) {
        return item;
    }

}