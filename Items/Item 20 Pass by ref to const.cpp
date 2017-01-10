/*
 * Preface Pass-by-reference-to-const over pass-by-value
 * 
 * 
 * C++ by default:
 *  - Passes by value to functions
 *  - Returns by value from functions
 *  
 *  These are done via the copy ctor of the Type.
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
