#pragma once

class SystemA
{
public:
    void OperationA() {}
};

class SystemB
{
public:
    void OperationB() {}
};

class Facade
{
public:
    Facade() 
    {
        systema_ = new SystemA();
        systemb_ = new SystemB();
    }
    virtual ~Facade() 
    {
        delete systema_;
        delete systemb_;
    }

    void WrapOpration()
    {
        systema_->OperationA();
        systemb_->OperationB();
     }

private:
    SystemA* systema_;
    SystemB* systemb_;
};

void test()
{
    Facade fa;
    fa.WrapOpration();

}