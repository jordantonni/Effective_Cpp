/*
 * Preface Pass-by-reference-to-const over pass-by-value
 * 
 * Pass Built in types, STL Iterator and Function Objects by Value
 * Pass everyting else as const reference
 * 
 * C++ by default:
 *  - Passes by value to functions
 *  - Returns by value from functions
 *  
 *  These are done via the copy ctor of the Type.
 *  Means that functions get and return COPIES of the object.
 *  
 *  Why const ref?
 *      - Pass by value copies the object, means the original is not modified
 *      - Const gives that same guarantee.
 *          - Unless you need to modify the original object, pass by const reference!
 *          
 *  Slicing
 *  Passing a derived object by value as a base object
 *      - Will call the base objects copy ctor, making the object a simple base class type
 *      - Derived parts will be "Sliced" off
 *      - Passing by reference will behave polymorphically and not slice.
 *          
 * References are implemented as pointers under the hood:
 *  - Therefore they are either 32-bit or 64-bit in size
 *  - Built in types are typically smaller than this, -> Pass built in types by value
 *      - Also pass STL Iterators and Function Objects by value
 *  
 */

#include <string>

namespace item20
{
    class base
    {
        std::string a;
        std::string b;
    };

    class derived : base
    {
        std::string c;
        std::string d;
    };

    /*
     * Invocation would result in 6 copy ctors and 6 dtors
     * 4 copy ctors for the strings a,,b,c,d
     * 1 for Type one
     * 1 for Type two
     * A dtor for every ctor
     */
    void pass_value(derived t);
}
