#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>


typedef uint32_t key;

// 只存name引用
struct User
{
    User(const string& fname, const string& lname) : first_name(add(fname)), last_name(add(lname))
    {
    }

    const string& get_first_name() const
    {
        return names.left.find(last_name)->second;
    }

    const string& get_last_name() const
    {
        return names.left.find(last_name)->second;
    }

    static void info()
    {
        for (auto entry : names.left) {
            cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
        }
    }
    friend ostream& operator<<(ostream& os, const User& obj)
    {
        return os
            << "first_name: " << obj.first_name << " " << obj.get_first_name()
            << " last_name: " << obj.last_name << " " << obj.get_last_name();
    }
protected:
    key first_name;
    key last_name;

    // 双向映射
    static boost::bimap<key, string> names;
    static key seed;

    static key add(const string& name)
    {
        auto it = names.right.find(name);
        if (it == names.right.end()) {
            // insert
            key id = ++seed;
            names.insert({id, name});
            return id;
        }

        return it->second;
    }
};
key User::seed = 0;
boost::bimap<key, string> User::names{};


// 使用boost.flyweights
struct User2
{
    boost::flyweights::flyweight<string> first_name, last_name;

    User2(const string& first_name, const string& last_name)
        : first_name(first_name),
        last_name(last_name)
    {
    }
};

void test()
{
    User john_doe{"John", "Doe"};
    User jane_doe{"Jane", "Doe"};

    cout << "John " << john_doe << endl;
    cout << "Jane " << jane_doe << endl;

    User::info();



    User2 user1{"John", "Smith"};
    User2 user2{"Jane", "Smith"};

    cout << user1.first_name << endl;

    cout << boolalpha
        << (&user1.first_name.get() == &user2.first_name.get()) << endl;
    cout << boolalpha
        << (&user1.last_name.get() == &user2.last_name.get()) << endl;

}

