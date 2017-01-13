#pragma once
#include <string>

class Item_31_PersonImpl
{
    std::string name;
    int age;

public:
    Item_31_PersonImpl(const std::string& name, int age);
    std::string Name() const;
    int Age() const;
};

