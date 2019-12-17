#pragma once
#include <algorithm>
#include <string>
#include <iostream>

class PersonBuilder;
class Personx
{
    // 住址信息
    std::string street_address, post_code, city;

    // 就业信息
    std::string company_name, position;
    int annual_income = 0;

    Personx()
    {
        std::cout << "person()" << "\n";
    }
public:
    ~Personx()
    {
        std::cout << "~person()" << "\n";
    }

    static PersonBuilder create();


    Personx(Personx&& other) noexcept
        : street_address{move(other.street_address)},
        post_code{move(other.post_code)},
        city{move(other.city)},
        company_name{move(other.company_name)},
        position{move(other.position)},
        annual_income{other.annual_income}
    {
    }

    Personx& operator=(Personx&& other)
    {
        if (this == &other)
            return *this;
        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Personx& obj)
    {
        return os
            << "street_address: " << obj.street_address
            << " post_code: " << obj.post_code
            << " city: " << obj.city
            << " company_name: " << obj.company_name
            << " position: " << obj.position
            << " annual_income: " << obj.annual_income
            << "\n";
    }

    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
    friend class PersonBuilder;
};
