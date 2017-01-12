#pragma once
#include <string>

class Person
{
    std::string name;
    int age;

public:
    Person(const std::string& name, int age);
    std::string Name() const;
    int Age() const; 
};