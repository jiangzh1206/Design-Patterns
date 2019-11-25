#include <iostream>
#include <string>
#include <memory>
using namespace std;

class LightSwitch;

struct State
{
    virtual void on(LightSwitch *ls)
    {
        cout << "Light is already on\n";
    }
    virtual void off(LightSwitch *ls)
    {
        cout << "Light is already off\n";
    }
};

struct OnState : State
{
    OnState()
    {
        cout << "Light turned on\n";
    }

    void off(LightSwitch* ls) override
    {
        cout << "Switching light off...\n";
        ls->set_state(new OffState());
    }
};

struct OffState : State
{
    OffState()
    {
        cout << "Light turned off\n";
    }

    void on(LightSwitch* ls) override
    {
        cout << "Switching light on...\n";
        ls->set_state(new OnState());
    }
};

class LightSwitch
{
    unique_ptr<State> state_;
public:
    LightSwitch()
    {
        state_.reset(new OffState());
    }
    void set_state(State* state)
    {
        state_.reset(state);
    }
    void on() { state_->on(this); }
    void off() { state_->off(this); }
};


void main_()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
    getchar();
}