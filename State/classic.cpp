#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct State;
struct OffState;

class LightSwitch
{
    unique_ptr<State> state_;
public:
    LightSwitch();
    void set_state(State* state);
    void on();
    void off();
};

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

    void off(LightSwitch* ls) override;
};

struct OffState : State
{
    OffState()
    {
        cout << "Light turned off\n";
    }

    void on(LightSwitch* ls) override;
};



inline LightSwitch::LightSwitch()
{
    state_.reset(new OffState());
}

inline void LightSwitch::set_state(State* state)
{
    state_.reset(state);
}

inline void LightSwitch::on() { state_->on(this); }

inline void LightSwitch::off() { state_->off(this); }


inline void OnState::off(LightSwitch* ls)
{
    cout << "Switching light off...\n";
    ls->set_state(new OffState());
}

inline void OffState::on(LightSwitch* ls)
{
    cout << "Switching light on...\n";
    ls->set_state(new OnState());
}


void main_2432()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
    getchar();
}
