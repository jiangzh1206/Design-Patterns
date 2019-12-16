#include <iostream>
#include <map>
#include <memory>

using namespace std;

struct HotDrink
{
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        cout << "prepare " << volume << "ml tea." << endl;
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        cout << "prepare " << volume << "ml coffee." << endl;
    }
};

#if 0
unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}
#endif // 0

// 抽象工厂，具有特定接口
struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};

// 具体工厂
struct TeaFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};

// 上层封装，关联string（enum...）
class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factory_;

public:
    DrinkFactory()
    {
        hot_factory_["coffee"] = make_unique<CoffeeFactory>();
        hot_factory_["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        auto drink = hot_factory_[name]->make();
        int volume = 500;
        drink->prepare(volume); // oops!
        return drink;
    }
};

void test()
{
    DrinkFactory df;
    df.make_drink("coffee");
    df.make_drink("tea");
}
