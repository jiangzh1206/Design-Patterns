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

// 给上边表达式添加访问行为，典型实现

struct IntExpression;
struct AddExpression;

struct ExpressionVisitor
{
    virtual void visit(IntExpression* ie) = 0;
    virtual void visit(AddExpression* ae) = 0;
};

struct Expression
{
    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct IntExpression : Expression
{
    int value_;
    explicit IntExpression(int v) : value_(v) {}

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
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

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss_;
    string str() const { return oss_.str(); }
    void visit(AddExpression* de) override
    {
        oss_ << "(";
        de->left_->accept(this);
        oss_ << "+";
        de->right_->accept(this);
        oss_ << ")";
    }
    void visit(IntExpression* ae) override
    {
        oss_ << ae->value_;
    }
};

struct ExpressionResult : ExpressionVisitor
{
    int result_;

    void visit(AddExpression* de) override
    {
        de->left_->accept(this);
        auto tmp = result_;
        de->right_->accept(this);
        result_ += tmp;
    }
    void visit(IntExpression* ae) override
    {
        result_ = ae->value_;
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

	ExpressionPrinter printer;
	ExpressionResult result;
	printer.visit(e);
	result.visit(e);
	cout << printer.str() << " = " << result.result_ << endl;
	// prints "(1+(2+3)) = 6"
}
