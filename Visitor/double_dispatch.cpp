
#if 0
struct Stuff {}
struct Foo : Stuff {}
struct Bar : Stuff {}

void func(Foo* foo) {}
void func(Bar* bar) {}

int main_()
{
    Foo* foo = new Foo;
    func(foo); // ok

    Stuff* stuff = new Foo;
    func(stuff); // oops! err
}
#endif
struct Foo;
struct Bar;

void func(Foo* foo) {}
void func(Bar* bar) {}

struct Stuff
{
    virtual void call() = 0;
};
struct Foo : Stuff
{
    void call() override { func(this); }
};
struct Bar : Stuff
{
    void call() override { func(this); }
};

// 1.多态获取真实对象，2.通过真实指针调用相应call()
int main_234525()
{
    Stuff* stuff = new Foo;
    stuff->call();  // call func(Foo*)

    return 0;
}