#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>

enum class PointType
{
    cartesian,
    polar,
};

class Point
{

#if 0 // 丑陋
    Point(float a, float b, PointType type = PointType::cartesian)
    {
        if (type == PointType::cartesian) {
            x = a; b = y;
        } else {
            x = a * cos(b);
            y = a * sin(b);
        }
    }
#endif // 0

protected: // 私有
    Point(float x, float y)
        : x_(x)
        , y_(y)
    {
    }

public:
    // 每个static方法都是个Factory Method
    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        return os << "x: " << p.x_
            << " y: " << p.y_;
    }

private:
    float x_;
    float y_;

    friend class PointFactory;

    // inner factory
    class InnerPointFactory
    {
        InnerPointFactory() {}

    public:
        static Point NewCartesian(float x, float y)
        {
            return {x, y};
        }
        static Point NewPolar(float r, float theta)
        {
            return {r * cos(theta), r * sin(theta)};
        }
    };

public:
    static InnerPointFactory factory_;
};

class PointFactory
{
public:
    static Point NewCartesian(float x, float y)
    {
        return Point{x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return Point{r * cos(theta), r * sin(theta)};
    }
};

// PointFactory，InnerPointFactory： factory
// static Point NewCartesian(float x, float y)： factory method

void test()
{
    auto p = Point::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    auto p1 = PointFactory::NewCartesian(10, 20);
    std::cout << p1 << std::endl;

    auto p2 = Point::factory_.NewCartesian(30, 40);
    std::cout << p2 << std::endl;
}