package src.ru.spbstu.main;

import src.ru.spbstu.main.shapes.Circle;
import src.ru.spbstu.main.shapes.Rectangle;
import src.ru.spbstu.main.shapes.Shape;
import src.ru.spbstu.main.shapes.Triangle;

public class Main {
    public static void main(String[] args) {
        Shape[] shapes = new Shape[10];

        Circle C1 = new Circle(1, 2, 3);

        Shape shape1 = new Circle(1, 2, 3);
        Shape shape2 = new Rectangle(1, 2, 3, 4, 6);
        Shape shape3 = new Triangle(1, 2, 3, 4, 5, 6, 7);

        shapes[0] = new Circle(1, 2, 3);
        shapes[1] = new Rectangle(2, 2, 3, 4, 96);
        shapes[2] = new Triangle(1, 2, 3, 4, 5, 6, 34);
        shapes[3] = new Circle(5, 7, 4);
        shapes[4] = new Rectangle(9, 2, 3, 3, 6);
        shapes[5] = new Triangle(1, 2, 3, 4, 5, 6, 12);
        shapes[6] = new Circle(1, 10, 3);
        shapes[7] = new Rectangle(-1, -5, 3, 4, 6);
        shapes[8] = new Triangle(-8, -9, 12, 2, 4, 8, 9);
        shapes[9] = new Circle(7, -3, 4);


        float maxArea = 0;
        for (int i = 0; i < 10; i++)
        {
            if (shapes[i].getArea() > maxArea)
            {
                maxArea = shapes[i].getArea();
            }
        }

        System.out.println(maxArea);

        /*
         * TODO: Выполнить действия над массивом 'shapes'
         *
         * 1. Проинициализировать переменную 'shapes' массивом
         *    содержащим 10 произвольных фигур. Массив должен
         *    содержать экземпляры классов Circle, Rectangle
         *    и Triangle.
         *
         * 2. Найти в массиве 'shapes' фигуру с максимальной
         *    площадью. Для поиска фигуры необходимо создать
         *    статический метод в текущем классе (Main).
         */
    }
}
