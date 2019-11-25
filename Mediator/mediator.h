#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person;

struct ChatRoom
{
    vector<Person*> people; // assume append-only

    void join(Person* p);
    void broadcast(const string& origin, const string& message);
    void message(const string& origin, const string& who, const string& message);
};

struct Person
{
    string name;
    ChatRoom* room = nullptr;
    vector<string> chat_log;

    Person(const string& name) : name(name){}
    void receive(const string& origin, const string& message)
    {
        string s{origin + ": \"" + message + "\""};
        cout << "[" << name << "'s chat session] " << s << "\n";
        chat_log.emplace_back(s);
    }
    void say(const string& message) const
    {
        room->broadcast(name, message);
    }
    void pm(const string& who, const string& message) const
    {
        room->message(name, who, message);
    }

    friend bool operator==(const Person& lhs, const Person& rhs)
    {
        return lhs.name == rhs.name;
    }

    friend bool operator!=(const Person& lhs, const Person& rhs)
    {
        return !(lhs == rhs);
    }
};



void ChatRoom::broadcast(const string& origin, const string& message)
{
    for (auto p : people)
        if (p->name != origin)
            p->receive(origin, message);
}

void ChatRoom::join(Person* p)
{
    string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

void ChatRoom::message(const string& origin, const string& who, const string& message)
{
    auto target = find_if(begin(people), end(people), [&](const Person* p) { return p->name == who; });
    if (target != end(people)) {
        (*target)->receive(origin, message);
    }
}



int test()
{
    ChatRoom room;

    Person john{"john"};
    Person jane{"jane"};
    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon("simon");
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("simon", "glad you could join us, simon");

    getchar();
    return 0;
}
