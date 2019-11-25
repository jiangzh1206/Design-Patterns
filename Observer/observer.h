#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>
using namespace std;

template<typename T>
struct Observer
{
    virtual void field_changed(T& source, const string& field_name) = 0;
};


template<typename T>
struct Observable
{
private:
    std::vector<Observer<T>*> observers_;
    mutex mtx;
public:
    void notify(T& source, const string& name)
    {
        vector<Observer<T>*> tmp;
        {
            // field_changed可在持有锁
            scoped_lock<mutex> lock{mtx};
            tmp = observers_;
        }
        for (auto ob : tmp) {
            if (ob) {
                ob->field_changed(source, name);
            }
        }
    }
    void subscribe(Observer<T>* observer)
    {
        scoped_lock<mutex> lock{mtx};
        if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
            observers_.push_back(observer);
        }
    }
    void unsubscribe(Observer<T>* observer)
    {
#if 0
        scoped_lock<mutex> lock{mtx};
        observers_.erase(
            remove(observers_.begin(), observers_.end(), observer),
            observers_.end());
#endif // 0

        // 避免使用锁，避免移除对象
        auto it = std::find(begin(observers_), end(observers_), observer);
        if (it != end(observers_)) {
            *it = nullptr;
        }
    }
};


struct Person : Observable<Person>
{
    Person(int age) : age_(age) {}

    void set_age(int age)
    {
        age_ = age;
        notify(*this, "age");
    }

    int get_age()
    {
        return age_;
    }

private:
    int age_;
};


struct ConsolePersonObserver : Observer<Person>
{
    void field_changed(Person& source, const string& field_name) override
    {
        cout << "Person's " << field_name << " changed to " << source.get_age() << endl;
    }
};





void test()
{
    Person p{20};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(21); // Person's age changed to 21.
    p.set_age(22); // Person's age changed to 22.
    //p.unsubscribe(&cpo);
    p.set_age(23);
}