/*
 * Use member function templates to accept "all compatiable types"
 * 
 * Different instantions of templates with different paramters are not related in any way
 *  - i.e. Widget<double> is not implicitly convertable to Widget<int> 
 *  
 * Member function templates (AKA. Member Template)
 *  - Usefull for constructors to allow for generalized copy constructors etc
 *  - Allows you to construct a templated type <A> from another templated type <B>
 * 
 * Still need to write non templated ctors and copy ctors and copy assignment etc
 *  - Compiler will still auto generate these functions if you define templated ones
 *      - For full control ensure you define them also!
 * 
 * SUMMARY:
 *  - Member function templates all you to generate functions that accept all types you need without making seperate methods for them
 *      - Useful for supporting ctors / assignment operators that can be instantited with other types
 *  - Templated ctors and assignment operators don't stop the compiler generated ones from being created
 */


namespace item45
{
    
}