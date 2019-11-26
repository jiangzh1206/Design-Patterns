#pragma once
#include <string>
#include "person.h"

// ���builder��Ϲ��쵥������

class Person;
class PersonJobBuilder;
class PersonAddressBuilder;
class PersonBuilder;

class PersonBuilderBase
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person {person} {}

public:
    operator Person()
    {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;

    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
    Person p;
public:
    PersonBuilder() : PersonBuilderBase(p) {}
};

// note: ��ֵ move  // prvalue ����ֵ, xrvalue std::move ���ص�
class PersonAddressBuilder : public PersonBuilderBase
{
    using self = PersonAddressBuilder;
public:
    explicit PersonAddressBuilder(Person& p) : PersonBuilderBase(p) {}
    self& at(std::string street_address)
    {
        person.street_address = std::move(street_address);
        return *this;
    }
    self& with_postcode(std::string post_code)
    {
        person.post_code = std::move(post_code);
        return *this;
    }
    self& in(std::string city)
    {
        person.city = std::move(city);
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder Self;
public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilderBase{person}
    {
    }

    Self& at(std::string company_name)
    {
        person.company_name = std::move(company_name);
        return *this;
    }

    Self& as_a(std::string position)
    {
        person.position = std::move(position);
        return *this;
    }

    Self& earning(int annual_income)
    {
        person.annual_income = annual_income;
        return *this;
    }
};


inline void builder_demo()
{
    Person p = Person::create()
        .lives().at("123 London Road")
        .with_postcode("SW1 1GB")
        .in("London")
        .works().at("PragmaSoft")
        .as_a("Consultant")
        .earning(10e6);

    std::cout << p;
}