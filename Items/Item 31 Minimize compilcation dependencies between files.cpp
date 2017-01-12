/*
 * Minimize compilation dependencies between files
 * 
 * 
 */

#include <string>
#include <iostream>
#include "Item 31 Person.hpp"

namespace item31
{
    using namespace std;

    void test()
    {
        Person me { "Jordan", 26 };
        cout << me.Name() << " " << me.Age() << endl;
    }
}
