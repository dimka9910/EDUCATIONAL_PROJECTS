package src.ru.spbstu.main.shapes;

/**
 * Представление об окружности.
 * <p>
 * Окру́жность — замкнутая плоская кривая, которая состоит из
 * всех точек на плоскости, равноудалённых от заданной точки.
 *
 * @see <a href="https://ru.wikipedia.org/wiki/%D0%9E%D0%BA%D1%80%D1%83%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D1%8C">Окружность</a>
 */
public class Circle implements Point, Ellipse, Shape {

    Point_t dot1;
    float radius_;


    public Circle(float x1, float y1, float r)
    {
        dot1 = new Point_t(x1,y1);
        radius_ = Math.abs(r);
    }

    public float getArea()
    {
        return (float)Math.PI * radius_ * radius_;
    }

    public float getLength()
    {
        return 2 * (float)Math.PI * radius_;
    }

    public float getX()
    {
        return dot1.x;
    }


    public float getY()
    {
        return dot1.y;
    }


    /*
     * TODO: Реализовать класс 'Circle'
     * 1. Используйте наследование.
     * 2. Реализуйте все абстрактные методы.
     */
}
