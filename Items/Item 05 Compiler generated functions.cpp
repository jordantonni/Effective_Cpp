/*
 * Know what functions the compiler writes itself and calls for classes.
 * 
 * Ctor, copy ctor, copy assingment op, dtor made for you by compiler if needed / used.
 * Purpose of default ctor is to init base class and non-static members
 * dtor is not virtual -> should define your own virtual dtor if using class in an inheritance tree
 * 
 * copy ctor will use memebers type copy ctor if they have one and just normal assingment on primitve member types
 * 
 * 
 * No copy assingment op will be made for a class that has reference or const memebers
 * Why?
 *  Because you can't change what a reference refers to, only the value of its data, this could break other code using it.
 *  Can't modify a const variable after it is initialized. So copy assingment into it makes no sense.
 *  
 * No copy assignment op for class that has a base with a private copy assignment op.
 * Why?
 *  Would be unable to copy assign the base portion of the class as it isnt availble to call. 
 *  This goes against the principle that a derived copy ass op should handle the base class portion also.
 */

#include <string>
#include <iostream>

namespace item05
{
    class EmptyClass
    { };

    // Compiler for above class will generate the following default ctors / dtors / assingment operators
    // As long as they are needed
    class RealEmptyClass
    {
        RealEmptyClass()
        {}

        RealEmptyClass(const RealEmptyClass& rhs)
        {}

        ~RealEmptyClass()
        {}

        RealEmptyClass& operator=(const RealEmptyClass& rhs)
        {}
    };

    /*
     * No copy assignment created by the compiler because it contains a reference and const
     * Both of these can't be changed easily so the compiler doesnt create them by default if present.
     */
    class NamedObject
    {
    public:
        std::string& name;
        const int value;

        NamedObject(std::string& na, int val)
            : name{ na }
            , value{ val }
        {}
    };

    void hehe()
    {
        std::string st { "hehe" };
        NamedObject no { st, 4 };

        std::cout << no.name << std::endl;
    }
}
