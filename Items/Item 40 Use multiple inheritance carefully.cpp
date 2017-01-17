/*
 * Use multiple inheritance carefully
 * 
 * Multiple inheritance means you can inherit a function with the same name twice
 *  - C++ only checks for accessability after checking the names, so it doesnt matter if one of the functions is private
 *  
 * Diamond Problem:
 *  - Same base class in inherited multuiple times due to each subclass you inherit from also inheriting from Base
 *  - Results in either having multiple copies (replication) of the base members or one copy
 *      - C++ defaults to multiple copies
 *  - Solution:
 *      - Virtual inheritance
 *          - class Sub1 : virtual public Base
 *          - class Sub2 : virtual public Base
 *          - class Derived : public Sub1, public Sub2
 *      - Most derived class is responsible for instantiating the virtual base now
 * 
 * SUMMARY:
 *  - Multiple inheritance can require virtual inheritance
 *  - Virtual inheritance adds size to classes and is slower to use
 *      - Try to ensure virtual bases have no data
 *  - One good way to use multiple inheritance is a public inheritance for interface combined with private inheritance for implementation
 */

#include <iostream>
using namespace std;


namespace item40
{
    /*
     * MI: Public inteface with private implementation
     */

    class IPerson
    {
    public:
        virtual ~IPerson();
        virtual std::string name() const = 0;
        virtual int age() const = 0;
    };

    class PersonImp
    {
    public:
        virtual std::string theName() const
        {
            return "John Smith";
        }

        virtual int theAge() const
        {
            return 42;
        }
    };

    /*
     * Inherits the IPerson pure virtual class to get the interface
     * Implements the functionly via private inheritance of the PersonImp class
     */
    class ConcretePerson : public IPerson, private PersonImp
    {
    public:
        virtual std::string name() const
        {
            return theName();
        }


        virtual int age() const
        {
            return theAge();
        }
    };
}
