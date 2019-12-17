#include <sstream>
#include <string>
#include <iostream>

using namespace std;

// cyclic visitor: based on function overloading
//                 works only on a stable hierarchy
// acyclic visitor: based on RTTI
//                  no hierarchy limitations, but slower

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase // marker interface
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;
    virtual void accept(VisitorBase& obj)
    {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&obj))
            ev->visit(*this);
    }
};

struct IntExpression : Expression
{
    int value_;
    explicit IntExpression(int value) : value_(value) {}

    virtual void accept(VisitorBase& obj)
    {
        using DEV = Visitor<IntExpression>;
        if (auto ev = dynamic_cast<DEV*>(&obj))
            ev->visit(*this);
    }
};

struct AddExpression : Expression
{
    Expression* left_, * right_;

    AddExpression(Expression* const left, Expression* const right)
        : left_(left), right_(right)
    {
    }

    ~AddExpression()
    {
        delete left_;
        delete right_;
    }

    virtual void accept(VisitorBase& obj)
    {
        using DEV = Visitor<AddExpression>;
        if (auto ev = dynamic_cast<DEV*>(&obj))
            ev->visit(*this);
    }
};


struct ExpressionPrinter : VisitorBase,
    Visitor<Expression>,
    //Visitor<IntExpression>,
    Visitor<AddExpression>
{
    void visit(Expression& obj) override
    {
        // fallback?
    }

    // can remove int visitor without failure
    //  void visit(IntExpression &obj) override
    //  {
    //    oss << obj.value;
    //  }

    void visit(AddExpression& obj) override
    {
        oss_ << "(";
        obj.left_->accept(*this);
        oss_ << "+";
        obj.right_->accept(*this);
        oss_ << ")";
    }

    string str() const { return oss_.str(); }
private:
    ostringstream oss_;
};


inline void test_43554()
{
    auto e = new AddExpression{
      new IntExpression{1},
      new AddExpression{
        new IntExpression{2},
        new IntExpression{3}
      }
    };
    ExpressionPrinter ep;
    ep.visit(*e);
    cout << ep.str() << "\n";
}
