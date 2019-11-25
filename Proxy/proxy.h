#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

// 1.The simplestand most direct illustration of the Proxy pattern is a smart pointer.
void smart_pointer_proxy()
{
    struct BankAccount
    {
        void deposit(int amount)
        {
            // ...
        }
    };

    BankAccount * ba = new BankAccount;
    ba->deposit(123);
    auto ba2 = make_shared<BankAccount>();
    ba2->deposit(123); // same API!
}

// 2.property proxy
template <typename T> struct Property
{
    T value;
    Property(const T initialValue)
    {
        *this = initialValue;
    }
    operator T()
    {
        // getter action
        return value;
    }
    T operator =(T newValue)
    {
        // setter action
        return value = newValue;
    }
};

void property_proxy()
{
    struct Creature
    {
        Property<int> strength{10};
        Property<int> agility{5};
    };

    Creature creature;
    creature.agility = 20;
    auto x = creature.strength;
    cout << creature.agility << endl;
}

// 3. virtual proxy  lazy instantiation
struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const string& name)
    {
        // load image
        cout << "Loading image from " << name << endl;
    }
    void draw() override
    {
        cout << "Drawing image" << endl;
    }
};

// load image when draw is used
struct LazyBitmap : Image
{
    Bitmap* bmp = nullptr;

    LazyBitmap(const string& name) {}
    ~LazyBitmap() { delete bmp; }
    void draw() override
    {
        if (!bmp) {
            bmp = new Bitmap();
        }
        bmp->draw();
    }
};

void virtual_proxy()
{
    LazyBitmap img{"pokemon.png"};
    img.draw();
    img.draw();
}