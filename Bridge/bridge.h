#pragma once
#include <iostream>

// bridge: 抽象接口，具体实现可不断变化
struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing circle of radius " << radius << std::endl;
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Drawing a vector circle of radius " << radius << std::endl;
    }
};

struct Shape
{
protected:
    Renderer& renderer; // bridge

    Shape(Renderer& renderer) : renderer{renderer}
    {
    }

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    float x, y, radius;

    void draw() override
    {
        // note: bridge
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override
    {
        radius *= factor;
    }

    Circle(Renderer& renderer, float x, float y, float radius)
        : Shape{renderer}, x{x}, y{y}, radius{radius}
    {
    }
};

void demo()
{
    {
        RasterRenderer rr;
        Circle raster_circle{rr, 5, 5, 5};
        raster_circle.draw();
        raster_circle.resize(2);
        raster_circle.draw();
    }
    {
        VectorRenderer rr;
        Circle raster_circle{rr, 5, 5, 5};
        raster_circle.draw();
        raster_circle.resize(2);
        raster_circle.draw();
    }
}
