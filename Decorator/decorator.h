#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <functional>

/*装饰器模式允许我们在不修改原始类型(开闭原则)或导致t爆炸的情况下增强现有类型*/

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;
    explicit Circle(const float radius)
        : radius(radius)
    {
    }
    void resize(float factor)
    {
        radius *= factor;
    }
    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle and radius is " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}

    explicit Square(const float side)
        : side{ side }
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

namespace danymic_decorator
{ // 动态装饰器
struct ColoredShape : Shape
{
    Shape& shape;
    std::string color;
    ColoredShape(Shape& shape, const std::string& color)
        : shape(shape)
        , color(color)
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, const uint8_t transparency)
        : shape{ shape }
        , transparency{ transparency }
    {
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};
} // namespace danymic_decorator

namespace static_decorator
{
template <typename T>
struct ColoredShape : T
{
    static_assert(std::is_base_of<Shape, T>::value, "template argument must be a shape!");
    std::string color;

    // need this (or not!)
    ColoredShape() {}

    template <typename... Args>
    ColoredShape(const std::string& color, Args... args)
        : T(std::forward<Args>(args)...)
        , color{ color }
    // you cannot call base class ctor here
    // b/c you have no idea what it is
    {
    }
    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <typename T>
struct TransparentShape : T
{
    static_assert(std::is_base_of<Shape, T>::value, "template argument must be a shape!");
    uint8_t transparency;

    template <typename... Args>
    TransparentShape(const uint8_t transparency, Args... args)
        : T(std::forward<Args>(args)...)
        , transparency{ transparency }
    {
    }
    std::string str() const override
    {
        std::ostringstream oss;
        oss << T::str() << " has the " << transparency << "% transparent";
        return oss.str();
    }
};

} // namespace static_decorator

namespace function_decorator
{ // 函数装饰器
struct Logger
{
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()>& f, const std::string& name)
        : func(f)
        , name(name)
    {
    }
    void operator()() const
    {
        std::cout << "entering name: " << name << std::endl;
        func();
        std::cout << "end entering name: " << name << std::endl;
    }
};

template <typename Func>
struct Logger1
{
    Func func;
    std::string name;
    Logger1(const Func& f, const std::string& name)
        : func(f)
        , name(name)
    {
    }
    void operator()() const
    {
        std::cout << "entering name: " << name << std::endl;
        func();
        std::cout << "end entering name: " << name << std::endl;
    }
};

template <typename Func>
auto make_logger1(Func func, const std::string& name)
{
    return Logger1<Func>{ func, name }; // () = call now
}

template <typename R, typename... Args>
struct Logger2;

// return type and argument list
template <typename R, typename... Args>
struct Logger2<R(Args...)>
{
    Logger2(std::function<R(Args...)> func, const std::string& name)
        : func{ func }
        , name{ name }
    {
    }

    R operator()(Args... args)
    {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }

    std::function<R(Args...)> func;
    std::string name;
};

template <typename R, typename... Args>
auto make_logger2(R (*func)(Args...), const std::string& name)
{
    return Logger2<R(Args...)>(std::function<R(Args...)>(func), name);
}
} // namespace function_decorator

void demo()
{
    using namespace danymic_decorator;
    Circle circle{ 0.5f };
    ColoredShape redCircle{ circle, "red" };
    std::cout << redCircle.str();
    // prints "A circle of radius 0.5 has the color red"

    std::cout << std::endl;

    Square square{ 3 };
    TransparentShape demiSquare{ square, 85 };
    std::cout << demiSquare.str();
    // A square with side 3 has 33.333% transparency

    std::cout << std::endl;

    TransparentShape myCircle{ redCircle, 79 };
    std::cout << myCircle.str();
    // A circle of radius 23 has the color green has 25.098% transparency
}

void demo1()
{
    using namespace static_decorator;
    TransparentShape<ColoredShape<Square>> blue_invisible_square{ 0, "blue", 10 };
    blue_invisible_square.color = "blue";
    blue_invisible_square.side = 321;
    std::cout << blue_invisible_square.str() << std::endl;
}

int f(int a)
{
    std::cout << a << std::endl;
    return 0;
}
double add(double a, double b)
{
    std::cout << a << "+" << b << "=" << (a + b) << std::endl;
    return a + b;
}
void demo2()
{
    using namespace function_decorator;

    Logger l(
        []() {
            std::cout << "function" << std::endl;
        },
        "test");
    l();

    Logger l1(std::bind(f, 10), "test1");
    l1();

    auto l2 = make_logger1(
        []() {
            std::cout << "function2" << std::endl;
        },
        "test2");
    l2();

    auto logged_add = make_logger2(add, "Add");
    auto result = logged_add(2, 3);
}