#include "person.h"
#include "composite_builder.h"

PersonBuilder Person::create()
{
    return PersonBuilder{};
}
