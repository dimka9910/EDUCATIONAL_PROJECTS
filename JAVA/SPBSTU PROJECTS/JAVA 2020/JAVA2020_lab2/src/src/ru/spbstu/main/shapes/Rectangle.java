package src.ru.spbstu.main.shapes;

/**
 * Представление о прямоугольнике.
 * <p>
 * Прямоугольник — четырехугольник, у которого все углы
 * прямые (равны 90 градусам).
 *
 * @see <a href="https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D1%8F%D0%BC%D0%BE%D1%83%D0%B3%D0%BE%D0%BB%D1%8C%D0%BD%D0%B8%D0%BA">Прямоугольник</a>
 */
public class Rectangle implements Shape, Point, Polygon {

    private Point_t centre_;
    private float width_;
    private float height_;
    private int angle_;

    public Rectangle(float x1, float y1, float height, float width, int angle)
    {
        angle_ = angle;
        centre_ = new Point_t(x1, y1);
        width_ = width;
        height_ = height;
    }

    public float getPerimeter()
    {
        return 2 * (width_ + height_);
    }

    public float getArea()
    {
        return width_ * height_;
    }


    public float getX()
    {
        return centre_.x;
    }


    public float getY()
    {
        return centre_.y;
    }


    @ Override
    public int getRotation()
    {
        return angle_;
    }

    /*
     * TODO: Реализовать класс 'Rectangle'
     * 1. Используйте наследование.
     * 2. Реализуйте все абстрактные методы.
     */
}
