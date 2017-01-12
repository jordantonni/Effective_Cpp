/*
 * Understand the ins and outs of inlining
 * 
 * Inline function: Replaces the function call with the body of the function itself where the invocation took place.
 * - No function call overhead
 * - More compiler optimizations can occur 
 * 
 * Implicit Inlining:
 * - Method defined within the class definition
 * 
 * Explicit Inlining:
 * - Prepend inline keyword on function signiture
 *
 * Inline functions have to be declared in a header file.
 * Why?
 *  - Inlining is typically a compile time operation ( C# and other managed languages can do it at runtime though)
 *  - Compiler needs to see the function body to copy it into the place where the invocation takes place
 *  - C++ compilers only see one translation unit at a time -> if inline function was in another cpp file its' definition can't be seen!
 *  - Header files are copied in at the top though, so it can see everything in there!
 *  
 * Note: This same reason is why templates are typically in header files
 *          - Compiler needs to see both the template body and the type it is invoked with in order to "stamp" out an instantiaton
 *          
 * Can't inline virtual functions.
 *  - Choosing what virtual function to use is run-time
 *
 * Can't inline functions called through function pointers or functions that have their addresses taken (need real function to take address of, obv)
 * 
 * Constructors and Destructors are NOT good candidiates for inlining
 * Why?
 *  - Default ctors call Base ctor + initialise data members via calling their ctors + handle all exceptions
 *      - If an exception is thrown the initialized data is destructed
 *  -> ctors and dtors are quite large!
 *  
 * Inlining functions mean changes to thhose functions result in a recompile of any file that invokes them!
 */


#include <iostream>

namespace item30
{
    class Person
    {
        int age;

    public:
        // This is implicity inlined by the compiler
        // Because it is defined in the class definition
        int get_age() const
        {
            return age;
        }

        int get_age_plus_one() const;
    };

    // Not implicitly inlined
    // Because it is defined outside the class definition
    int Person::get_age_plus_one() const
    {
        return age + 1;
    }

    //Explicit inline
    inline void func(int y)
    {
        std::cout << y << std::endl;
    }

    void test()
    {
        //func(1337);   Would be replaced with below
        std::cout << 1337 << std::endl;
        
    }


}
