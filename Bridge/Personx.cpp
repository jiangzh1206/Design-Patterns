#include "Personx.h"

namespace bridge
{
struct Personx::PersonImpl
{
    void greet(Personx* p);
};

void Personx::PersonImpl::greet(Personx* p)
{
    printf("hello %s", p->name.c_str());
}

Personx::Personx()
    : impl(new PersonImpl)
{
}

Personx::~Personx()
{
    delete impl;
}

void Personx::greet()
{
    impl->greet(this);
}

}
