/*
 * Define non-member functions inside templates when type conversions are desired
 * 
 * (Item 24) Non member functions can provide implicit type conversions between all args - Implicit this pointer doesnt allow it for memeber functions.
 *  - Implicit type conversions like using a non-explicit ctor allow for this
 * 
 * To support this for templated functions we have problems:
 *  - Compiler needs to figure out the types of the arguments passed in, in order to instantiate a function with those types.
 *  - Implicit type conversions are NEVER considered for template argument deduction
 *      -> Meaning, there is no way to convert some a type U to a templated<T> using its' ctor, so it can't figure out what to use as T
 * 
 * Class Templates don't require template argument deduction, only function templates do
 *  - Declare the templated functions as a friend 
 *  - Means T is known at compile time
 *  - Templated function is instantiated with the correct T types
 *      -> Meaning, it can now be called with some type U, as long as there is a conversion availble from U to T
 *      - Why? Because the templated function is now an instantiated FUNCTION, not a function template, as implicit conversion works in functions.
 *      
 *      
 * Ensure you define the friend function inside the class also
 *  - This is needed for the linker
 * 
 * SUMMARY:
 *  - If a class template offers functions where all parameters need to be implicity converted, such as operator*,
 *    define those as friends inside the class template
 */


namespace item46
{
    
}
