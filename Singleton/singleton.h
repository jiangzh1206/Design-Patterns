#pragma once

// 单例
struct SingleTon
{
protected:
    SingleTon() {}

public:
    static SingleTon& get()
    {
        static SingleTon s;
        return s;
    }

    SingleTon(SingleTon&) = delete;
    SingleTon& operator =(SingleTon&) = delete;

    //note: 拷贝构造delete 不会自动生成移动拷贝
    //SingleTon(SingleTon&&) {}
    //SingleTon& operator =(SingleTon&&) { return *this; }
};

template<typename T>
class Instance
{
public:
    static T& Get()
    {
        static T obj;
        return obj;
    }
};

void demo()
{
    auto& ss = SingleTon::get();
    //ss = std::move(ss);
    //auto s = std::move(ss);
    //SingleTon s = SingleTon();

    struct Obj {};
    auto obj = Instance<Obj>::Get();
}