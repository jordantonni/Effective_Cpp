/*
 * Minimize Casting
 * 
 * C++ Casting is not as safe as it is in Java, C# and C.
 * 
 * Old-Style Casts: Both are equilivant in casting expression to Type
 * - C-Style cast:          (Type) expression
 * - Function-Style cast:   Type (expression)       //Constructor call in a argument is a function style cast 
 * 
 * New-Style Casts: More readable and purpose specific.
 * - const_cast: Remove const'ness from an object
 *
 * - dynamic_cast: Safe casting from a base to a more derived type.
 *                 Has runtime costs (string comparison on type names)
 *                 
 * - static_cast: Force implicit type conversions, such as int to double.
 *                Can add const, but cannot remove it. Only const_cast can do that.
 *                
 * - reinterpret_cast: low-level cast that give unportable code.
 *                     Treat an object as though it was another type.
 *                     Rare to use.
 *                     Dangerous!
 *                     
 * Type conversions result in code generation -> more runtime cost.
 * - An int to a double changes how the type is stored -> code generation
 * - A derived class object can have MULTIPLE addresses:
 *  - Address of derived part
 *  - Address of base part
 *      - Base* pb = *dp;   // derived *dp pointer has an offset applied at runtime to turn it into base *bp pointer!
 *      
 * 
 * Don't cast up to call base functions:
 * - Instead of static_cast<BaseName> (*this).someMethod();     // Results in a COPY of the base portion being created and invoked on! Not the original object
 * - Use BaseName::someMethod();
 * 
 * Instead of using dynamic_cast to check if you can invoke a dervied function on some object:
 * - Store the derived pointers instead of base pointers if you can
 *  - This obviously means you can no longer have a polymorphic collection of all the types in the hierarchy. 
 * - If that is needed then you could create a no-op virtual function in the base and always call it without checking.
 * 
 * Never have cascading calls to dynamic_cast
 * - i.e. never have multiple if(dynamic_cast<typeA>) ... checks
 *  - Will results in lots of expensive checks
 *  - Will have to add more if you add a new dervied type
 * - This pattern indicates a need for a virtual function call instead!
 * 
 * SUMMARY:
 *  - Avoid casts if possible, espically dynamic_cast
 *  - Hide casting by encapsulating it in functions
 *  - Use new style casts over old style
 *  
 * 
 */

namespace item27
{
    int x = 5;
    double d = (double)x; //Old cast
    double dd = double(x);// Old function cast

    class base
    {
    public:
        virtual ~base();
        virtual void something() {};
    };

    class derived : public base
    {
        virtual void something()
        {
            // Do not do this -> results in a copy of the base portion being created and used
            static_cast<base>(*this).something();

            // This is correct way to call base method on implicit *this
            base::something();
        }
    };

    class derivedTwo : public base
    {};

    /*
     * Very slow code due to runtime costs of dynamic_cast
     * Instead this indicated that whatever would be called within the body of the if should be a virtual function
     */
    void bad(base* b)
    {
        if(derived* dp = dynamic_cast<derived*>(b))
        {

        }
        else if(derivedTwo* d2p = dynamic_cast<derivedTwo*>(b))
        {
            
        }
    }
}
