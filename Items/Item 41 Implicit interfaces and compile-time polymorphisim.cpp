/*
 * Understand implicit interfaces and compile-time polymorphisim
 * 
 * Explicit Interface -> Function signitures 
 * Implicit Interface -> The operators and functions that are called in a template must be supported by whatever type you pass in
 * 
 * Run-Time Polymorphisim -> Virtual functions called based on dynamic type of object
 * Compile-Time Polypmorphisim -> Different templated functions will be instantiated depending on the types passed in to a template
 * 
 * 
 * Note: 
 *  Although the Implicit interface is detmined by the expressions the template contains
 *  meaning whatever type is passed in must support those expressions and operations.
 *  As long as the type passed in can be converted to types the expressions need it is fine!
 *  
 * 
 * SUMMARY:
 *  - Classes and Templates support interfaces and polymorphisim
 *  - Classes:
 *      - Interfaces are explicitly defined and focused on functions that are public
 *      - Polymorphisim occurs at run-time using virtual functions
 *  -Templates:
 *      - Interfaces are implicit and determined by the valid expressions for the type passed in
 *      - Polymorphiskm occurs a compile-time using template instantiation and overload resolution
 */

namespace item41
{
    /*
     * Here whatever type you pass in must support the following implicit interface:
     * - Contain a size method, normalize method and swap method
     * - Either have size return an int or something that can be used on a operator>(int), possibly overloading it
     * - Support operator!= or be converted into a type that does support that operator for typeof(someNastyThing) 
     */
    template <typename T>
    void doProcessing(T& w)
    {
        if (w.size() > 10 && w != someNastyThing)
        {
            T temp(w);
            temp.normalize();
            temp.swap(w);
        }
    }
}
