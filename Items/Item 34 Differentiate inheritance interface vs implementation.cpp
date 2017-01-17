/*
 *Differentiate between inheritance of interface and inheritance of implementation
 *
 * Precisely specify what dervied classes inherit
 *  - Pure Virtual -> Interface only
 *  - Virtual      -> Interface + Default implementation (can specialize and change)
 *  - Non-Virtual  -> Interface + Mandatory implementation (can't change)
 *  
 * Seperating functions from interface and implementation - Via splitting default virtual functions
 *  - Instead of having fly be virtual to provide a default implementation, we make it pure virtual and put a default fly implementation in protected section.
 *  - Any class that wants the deafult behavior just has to forward to default_fly in their fly override.
 *  - Can also be done via pure virtual implementation, both shown below
 *  - Why? 
 *      - Stops classes from accidently inheritating default behavior they shouldnt support!
 * 
 * Non-Virtual functions
 *  - Specify an INVARIANT over the hierarchy of specializations
 * 
 * SUMMARY:
 *  - Inheritance of interface is different from inheritance of impmentation
 *  - Public inheritance -> defived classes always inherit base class interface
 *  - Pure virtual -> interface only
 *  - Virtual -> interface +  default implementation
 *  - Non-Virtual -> Interface + mandatory (invariant) implementation
 */

#include <iostream>
using namespace std;

namespace item34
{
    class Aeroplane
    {
    protected:
        virtual void default_fly()
        {
            // do some stuff
        }
    public:
        virtual void fly() = 0;
    };

    void Aeroplane::fly()
    {
        // Could also add a default implementation to the pure virtual function here. 
    }


    /*
     * Derived class specifies it wants default implementation, instead of just getting it automatically 
     */
    class SpecialPlane : Aeroplane
    {
    public:
        virtual void fly()
        {
            default_fly(); 

            Aeroplane::fly(); // Another way to ask specifically for default behaviour using a pure virtual implementation!
        }
    };


    void test()
    { }
}
