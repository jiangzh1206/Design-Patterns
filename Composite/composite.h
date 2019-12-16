#pragma once
#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>
#include <vector>

class Creature
{
    enum Abilities { str, agi, intl, count };
    // ¡¶¡ø,√ÙΩ›,÷«¡¶
    // int strength, agility, intelligence;
    std::array<int, count> abilities;
public:
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value; }

    int get_agility() { return abilities[agi]; }
    void set_agility(int value) { abilities[agi] = value; }

    int get_intelligence() const { return abilities[intl]; }
    void set_intelligence(int value) { abilities[intl] = value; }

    int sum() const { return std::accumulate(abilities.begin(), abilities.end(), 0); }
    double average() const { return sum() / double(count); }
    int max() const { return *std::max_element(abilities.begin(), abilities.end()); }
};


struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicObject
{
    void draw() override { std::cout << "Circle" << std::endl; }
};

struct Group : GraphicObject
{
    std::string name;
    std::vector<GraphicObject*> objects;

    explicit Group(const std::string& name)
        : name{name}
    {
    }

    void draw() override
    {
        std::cout << "Group " << name.c_str() << " contains:"
            << std::endl;
        for (auto&& o : objects)
            o->draw();
    }
};

void test()
{
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();
}