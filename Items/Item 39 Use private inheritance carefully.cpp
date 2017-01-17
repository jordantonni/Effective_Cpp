/*
 * Use Private inheritance carefully
 * 
 * Public Inheritance: Is-a
 *  Compilers will implicitly convert Derived type to Base when neccessary
 *  Does NOT happen in private inheritance
 *  
 * Private Inheritance: Is-Implemented-In-Terms-Of
 *  - Implementation only should be inherited, Not the interface
 *  - This is why everything in the base class becomes private in the derived class using private inheritance!
 *  
 * E.G. Get timing functionality from a Timer class by privately inheriting from it and using its' onTick() method
 * 
 * Using nested composition with public inheritance instead:
 *  - You can instead declare a private nested class that dervies from the timer class inside.
 *  - Override the timer functionality in the private nested class
 *  - Use the derived nested class instead!
 *  
 * Empty Base Class Optimization (EBO)
 *  - Empty -> Can still have static members, non-virtual functions, typedefs, enums. Just not non-static members
 *  - Empty classes still have a size, usually sizeof(char) but often more due to padding
 *  - "Empty" classes don't have a size if they are inherited from!
 *      -> Can use private inheritance to get the functionality of the "Empty" class without incurring extra size though composiiton
 *  
 *  SUMMARY:
 *      - Private inhertiance means Is-implemented-in-terms-of, just like composition
 *      - Use composition instead of private inheritance unless:
 *          - Need access to protected base class members or redefine virtual functions
 *      - Private inheritance can enable Base Class Optimization, not useful outside librarys really
 * 
 */

#include <string>

namespace item39
{
    class Person
    { };

    class Student : private Person
    {};

    void eat(Person& p)
    {}

    void test()
    {
        Person p;
        Student s;

        eat(p);
        // eat(s);      // Error, private inheritance means Student is NOT a Person -> No implicit conversion
    }


    /*
     * Nested composition with public inheritance over private inheritance
     */

    class Timer
    {
    public:
        virtual void doStuff()
        {
            int x = 3; //Do stuff
        }
    };

    class Widget
    {
    private:
        class WidgetTimer : public Timer
        {
        public:
            virtual void doStuff()
            {
                float x = 33.33f;
            }
        };

        WidgetTimer timer; // Can use this nested specialised type instead of private inhertiance of the Timer to get stuff done
    };
}
