#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct BankAccount
{
    int balance_ = 0;
    int overdraft_limit_ = -500;

    // ´¢Ðî
    void deposit(int amount)
    {
        balance_ += amount;
        cout << "deposited " << amount << ", balance now is " << balance_ << endl;
    }
    // È¡Ç®
    void withdraw(int amount)
    {
        if (balance_ - amount >= overdraft_limit_) {
            balance_ -= amount;
            cout << "withdrew " << amount << ", balance now " << balance_ << endl;
        }
    }

    friend ostream& operator << (ostream& os, const BankAccount& ba)
    {
        os << "balanc:" << ba.balance_;
        return os;
    }
};

struct Command
{
    bool succeeded_;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account_;
    int amount_;
    enum Action{D, W} action_;

    BankAccountCommand(BankAccount& account, Action action, int amount)
        : account_(account), amount_(amount), action_(action)
    {
        succeeded_ = false;
    }

    void call() override
    {
        switch (action_) {
        case BankAccountCommand::D:
            account_.deposit(amount_);
            succeeded_ = true;
            break;
        case BankAccountCommand::W:
            account_.withdraw(amount_);
            break;
        default:
            break;
        }
    }

    void undo() override
    {
        if (!succeeded_) return;
        switch (action_) {
        case BankAccountCommand::D:
            account_.withdraw(amount_);
            break;
        case BankAccountCommand::W:
            account_.deposit(amount_);
            break;
        default:
            break;
        }
    }
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const initializer_list<value_type>& items)
        : vector<BankAccountCommand>(items) {}

    void call() override
    {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() override
    {
        for (auto& cmd : *this)
            cmd.undo();
    }
};


void test()
{
    BankAccount ba;
    CompositeBankAccountCommand commands{
      BankAccountCommand{ba, BankAccountCommand::D, 100},
      BankAccountCommand{ba, BankAccountCommand::W, 200}
    };

    cout << ba.balance_ << endl;

    commands.call();
    cout << ba.balance_ << endl;

    commands.undo();
    cout << ba.balance_ << endl;


    vector<BankAccountCommand> commands1
    {
      BankAccountCommand{ba, BankAccountCommand::D, 100},
      BankAccountCommand{ba, BankAccountCommand::W, 200}
    };

    cout << ba << endl;
    for (auto& cmd : commands1) {
        cmd.call();
    }

    for (auto it = commands1.rbegin(); it != commands1.rend(); ++it) {
        it->undo();
    }
    cout << ba << endl;

}