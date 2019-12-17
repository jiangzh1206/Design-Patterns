#include "bridge.h"
#include <list>

int main0()
{
    std::list<int> l{1, 2, 3};
    auto size = l.size();

    demo();
    return 0;
}