#include <sstream>
#include <string>
#include <iostream>


using namespace std;

// 表达式，（1 + （2 + 3））
namespace express
{
struct Expression
{
    ;
};

struct IntExpression : Expression
{
    int value_;
    explicit IntExpression(int value) : value_(value) {}
};

struct AddExpression : Expression
{
    Expression* left_, *right_;

    AddExpression(Expression* const left, Expression* const right)
        : left_(left), right_(right)
    {
    }

    ~AddExpression()
    {
        delete left_;
        delete right_;
    }
};
}

// 给上边表达式添加访问行为，浸入式
struct Expression
{
    virtual void print(ostringstream& oss) = 0;
};

struct IntExpression : Expression
{
    int value_;
    explicit IntExpression(int v) : value_(v) {}

    void print(ostringstream& oss) override
    {
        oss << value_;
    }
};

struct AddExpression : Expression
{
    Expression* left_, *right_;

    AddExpression(Expression* const left, Expression* const right)
        : left_(left), right_(right)
    {
    }

    ~AddExpression()
    {
        delete left_;
        delete right_;
    }

    void print(ostringstream& oss) override
    {
        oss << "(";
        left_->print(oss);
        oss << "+";
        right_->print(oss);
        oss << ")";
    }
};


inline void test()
{
    auto e = new AddExpression{
      new IntExpression{1},
      new AddExpression{
        new IntExpression{2},
        new IntExpression{3}
      }
    };
    ostringstream oss;
    e->print(oss);
    cout << oss.str() << endl;
}
