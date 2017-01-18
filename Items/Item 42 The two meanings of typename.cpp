/*
 * Understand the two meanings of typename
 * 
 * typename and class can be used interchangably in the following:
 *  template <typename T> 
 *  template <class T>
 * 
 * Dependent Names: Name of something that is dependent on the template parameter | i.e. T
 * Nested Dependent Name: Dependent name that is nested inside a class | i.e. T::some_value
 * Nested Dependent Type Name: Same as above but the name corresponds to a type | i.e. T::const_iterator iter (iter is a NDTN)
 * Non-Dependent Name: Not depedent on any of the template parameters | i.e. int
 * 
 * Nested Dependent Type Name problems:
 *  - C++ compiler doesnt know if a nested dependent name is a type or a value or whatever
 *      - C::const_iterator* v; could mean instead of a pointer to that type, multiply v by the value of const_interator in C
 *  - Compiler treats all nested dependent names as NON-types
 *  - Force compiler to treat it as a type by putting typename before it
 *      - typename C::const_iterator iter
 * 
 * When to use it?:
 *  - Only on nested dependent type names
 *  - Not on nested dependent type names in the list of base classes to inherit from
 *  - Not in the base class in a ctor memeber initializer list
 * 
 * typedefs:
 *  - Because writing: typename T::const_iterator can be long and even longer
 *  - Write instead: typedef typename T::const_iterator Tconit
 * 
 * SUMMARY:
 *  - typename and class are interchangable in class and function parameters
 *  - Precede nested dependent type names with typename, unless in inheritance specifier or member init list
 */

namespace item42
{   
    template<typename> // Fwrd decl
    class Base;

    template<typename T>
    class Derived : public Base<T>::Nested  // Don't use typename here
    {
    public:
        Derived(int x)
            : Base<T>::Nested(x)    // Don't use typename here
        {
            typename Base<T>::Nested temp; // Use typename here
        }
    };
}