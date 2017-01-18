/*
 * Know how to access names in templated base classes
 * 
 * Inheriting from a templated class can cause problems with knowing what the base class contains
 *  - Calling a method from the base class, the compiler doesnt know it exists, why?
 *      - Templated base class is only instantiated once you pass a type paramter to it and use it
 *      - Total template specializations means some versions of the template will and wont have certain members
 *      -> Compiler doesnt know if methods will exist at compile time for the derived class to call!
 *      
 * Total Template Specialization:
 *  template<>
 *  class Widget<Person>{
 *   ....
 *  }
 *  
 *  - template<> signifies class Widget isnt a template nor a normal class, it is specialized
 *  - <Person> signigies to use this version of the template when instantiated with a Person type
 *  - Total because once Person is specified, no other aspect of the templates paramters can vary
 *      
 * TLDR: Compiler doesnt look in templated base classes for inherited names
 *       Need to force it to via:
 *       1) Prefacing method invocations with this | this->Method();
 *       2) Using declaration of base class | using BaseClass<Name>::Method();
 *       3) Specify function from base class | BaseClass<Name>::Method(val);
 *       
 *       Prefer 1 or 2. 3 Stops virtual binding so no polymorphisim.
 * 
 * SUMMARY:
 *  - If a derived class inherits from a templated base class, use "this->" prefix on method calls or using declarations to
 *    access base class methods.
 *
 */

namespace item43
{
    template<typename T>
    struct Base
    {
        void someMethodA() {}
        void someMethodB() {}
    };

    template<>
    struct Base<int>
    {
        void someMethodA() {} // In this total specialization for int, we don't declare a someMethodB, so it wouldn't be able to be called in derived for int
    };

    template<typename T>
    struct Derived : public Base<T>
    {
        void forwardMethod()
        {
            using Base<T>::someMethodA; // Lets compiler know this method exists to call

            someMethodA();
        }
    };

    void test()
    {
        
    }
}
