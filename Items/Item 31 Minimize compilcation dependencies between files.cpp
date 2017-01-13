/*
 * Minimize compilation dependencies between files
 * 
 * Use references & pointers instead of objects.
 * Depend on declarations and not class definitions.
 * 
 * Compiler needs the definition of classes in order to define a varible of that type.
 * As they need to know its size to store on stack
 *  - Only need the declaration for a pointer, reference or function signiture.
 * 
 * Java / .NET doesnt have this problem as behind the scenes objects are references.
 * We can do the same in C++, just explictly use pointers. 
 * 
 * 
 * 2 Main ways - PIMPL & Interfaces
 * 
 * PIMPL - Pointer to implementation
 * - Seperates interface from implementations
 * - Main class defines the interface to expose to clients
 *  - Has a pointer to impl class
 * - Implementation class defines the data memebers and the methods
 *  - Main class delegates though its pimpl
 * 
 * Pros -> client of class is only dependent on the interface, not the implementation which is stored in impl
 * 
 * INTERFACE - Abstract class (Class with at least 1 pure virtual function)
 * - Define the interface in the abstract class
 * - Inherit the interface and implement it
 *  - Either by a static method in the interface class that returns one of the derived implementations (chooses via the arguments passed)
 *  - Instantiate one of the dervied classes directly
 * 
 * SUMMARY:
 *  - Have client code depend on declarations, not definitions.
 *      - Via PIMPL or Interfaces
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
