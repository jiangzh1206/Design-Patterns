#include <iostream>

namespace mcpp
{
using namespace std;

class ManDay{
public:
	void go()
	{
		cout << "man's day go go go" << endl;
		eat();
		sleep();
		beat_beans();
	}

protected:
	virtual void eat() = 0;
	virtual void sleep() = 0;
	virtual void beat_beans() = 0;
};

class Ming : public ManDay{
public:
	Ming()
	{
		cout << "this is Ming!" << endl;
	}
protected:
	void eat() override{
		cout << "ming eat rice" << endl;
	}
	
	void sleep() override{
		cout << "ming sleep 12h" << endl;
	}
	
	void beat_beans() override{
		cout << "ming beat beans!!!" << endl; 
	}
};

class Hong : public ManDay
{
protected:
	void eat() override {}
	void sleep() override {}
	void beat_beans() override {}
};

}

using namespace mcpp;

void test_23423()
{
	Ming ming;
	ming.go();

	Hong hong;
	hong.go();
}
