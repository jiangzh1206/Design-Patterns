#include "composite_builder.h"

PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{person};
}
