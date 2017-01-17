/*
 * Never redefine a functions's inherited default parameter values
 * 
 * Virtual functions are dynamically bound
 *  - The function that is invoked depends on the dynamic type of the object
 *  
 * Default parameter values are statically bound
 *  - The value of the parameter is got from the static type of the object
 *  
 * Static Binding == Early Binding
 * Dynamic Binding == Late Binding
 * 
 *    
 * Static type = Type you declare an object of in the program text
 *  - Base* bp = new Derived; 
 *      - Staic type BASE
 *      - Dynamic type DERVIED
 * Dynamic Type = Type that the object currenrly refers to
 *  - Dynamic type specifies its' behavior
 *  
 *  SUMMARY:
 *      - Default parameters are statically bound, but the function to invoke is dynamically bound
 *      - If you redefine a virtual functions default parameter values, the derived function will still be called, but with the default param
 *        value specified in the base class.
 *
 */

#include <iostream>

namespace item37
{
    struct B
    {
        virtual int foo(int x = 100)
        {
            return x;
        }
    };

    struct D : public B
    {
        virtual int foo(int x = 1337)
        {
            return x;
        }
    };

    void test()
    {
        using namespace std;
        D d;
        B* point = &d;
        cout << point->foo() << endl; //Will print out 100, as the default param is statically bound
    }
}
