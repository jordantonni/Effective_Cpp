#include "Item_31_PersonImpl.h"


Item_31_PersonImpl::Item_31_PersonImpl(const std::string& name, int age)
    : name { name }
    , age { age }
{}

std::string Item_31_PersonImpl::Name() const
{
    return name;
}

int Item_31_PersonImpl::Age() const
{
    return age;
}
