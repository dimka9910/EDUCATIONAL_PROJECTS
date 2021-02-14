package src.ru.spbstu.main.shapes;

/**
 * Представление о треугольнике.
 * <p>
 * Треуго́льник (в евклидовом пространстве) — геометрическая
 * фигура, образованная тремя отрезками, которые соединяют
 * три точки, не лежащие на одной прямой. Указанные три
 * точки называются вершинами треугольника, а отрезки —
 * сторонами треугольника. Часть плоскости, ограниченная
 * сторонами, называется внутренностью треугольника: нередко
 * треугольник рассматривается вместе со своей внутренностью
 * (например, для определения понятия площади).
 *
 * @see <a href="https://ru.wikipedia.org/wiki/%D0%A2%D1%80%D0%B5%D1%83%D0%B3%D0%BE%D0%BB%D1%8C%D0%BD%D0%B8%D0%BA">Треугольник</a>
 */
public class Triangle implements Shape, Point, Polygon {

    private Point_t a_;
    private Point_t b_;
    private Point_t c_;
    private int angle_;

    private float sq(float n)
    {
        return n * n;
    }

    public Triangle(float x1, float y1, float x2, float y2, float x3, float y3, int angle)
    {
        angle_ = angle;
        a_ = new Point_t(x1,y1);
        b_ = new Point_t(x2,y2);
        c_ = new Point_t(x3,y3);
    }

    public float getPerimeter()
    {
        float aa = (float)(Math.sqrt(sq(a_.x - b_.x) + sq(a_.y - b_.y)));
        float bb = (float)(Math.sqrt(sq(b_.x - c_.x) + sq(b_.y - c_.y)));
        float cc = (float)(Math.sqrt(sq(a_.x - c_.x) + sq(a_.y - c_.y)));
        return aa + bb + cc;
    }

    public float getArea()
    {
        return Math.abs((a_.x - c_.x) * (b_.y - c_.y) - (b_.x - c_.x) * (a_.y - c_.y)) / 2;
    }

    public float getX()
    {
        return (a_.x + b_.x + c_.x) / 3;
    }


    public float getY()
    {
        return (a_.y + b_.y + c_.y) / 3;
    }

    @Override
    public int getRotation()
    {
        return angle_;
    }

    /*
     * TODO: Реализовать класс 'Triangle'
     * 1. Используйте наследование.
     * 2. Реализуйте все абстрактные методы.
     */
}
