#pragma once
#include <string>
#include <memory>
#include "Item_31_PersonImpl.h"

class Person
{
    std::shared_ptr<Item_31_PersonImpl> pImpl;

public:
    Person(const std::string& name, int age);
    std::string Name() const;
    int Age() const;
};
