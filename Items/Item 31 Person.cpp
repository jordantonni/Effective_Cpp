#include  "Item 31 Person.hpp"

Person::Person(const std::string& name, int age)
    : name{ name }
    , age{ age }
{ }

std::string Person::Name() const
{
    return name;
}

int Person::Age() const
{
    return age;
}
