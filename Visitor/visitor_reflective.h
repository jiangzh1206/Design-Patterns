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

// 给上边表达式添加访问行为，反射式
struct Expression
{
    virtual ~Expression() = default;
};

struct IntExpression : Expression
{
    int value_;
    explicit IntExpression(int v) : value_(v) {}
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

struct ExpressPrinter
{
	ostringstream oss_;
	string str() const {return oss_.str();}
	
	void print(Expression* e) 
	{
		if (auto ie = dynamic_cast<IntExpression*>(e)) {
			oss_ << ie->value_;
		} else if (auto ae = dynamic_cast<AddExpression*>(e)) {
			oss_ << "(";
			print(ae->left_);
			oss_ << "+";
			print(ae->right_);
			oss_ << ")";
		}
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
  ExpressPrinter ep;
  ep.print(e);
  cout << ep.str() << endl;
}
