#include  "Item 31 Person.hpp"
#include "Item_31_PersonImpl.h"

Person::Person(const std::string& name, int age)
    : pImpl { new Item_31_PersonImpl(name, age) }
{ }

std::string Person::Name() const
{
    return pImpl->Name();
}

int Person::Age() const
{
    return pImpl->Age();
}
