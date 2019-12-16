#include "composite_builder.h"
#include "simple_builder.h"

struct S {
    void ff() const { std::cout << "ff()" << std::endl; }
    void f() &
    {
        std::cout << "f()" << std::endl;
    }
    void f() && { std::cout << "f()&&" << std::endl; }
};

int main_()
{
    {
        S s;
        s.f();
        (new S)->f();
        S().f();
        auto ts = []() {
            return S();
        };
        ts().f();
    }

    simple_test();

    builder_demo();

    return 0;
}