/*
 * Model "has-a" or "is-implemented-in-terms-of" via composition, NOT public inheritance
 * 
 * Composition: when one type contains objects of another type
 * 
 * Public Inheritance -> Is-a
 * 
 * Application Domain: Correspond to things in real world.  People, Vehicles
 * Inplementation Domain: Correspond to things needed in your program. Buffers, Mutexs, B-Trees
 * 
 * Composition:
 *  - Has-A                     -> Application domain: composition is used to correspond to objects in the real world (i.e. string for name in Person type)
 *  - Is-Implmented-In-terms-of -> Implementation domain: composition is used for the implementation of the type (i.e. a mutex in a type)
 *  
 *  
 *  E.G. Don't use inheritance to implement a set by inheriting from list
 *      - Why?
 *          - Public Inheritance means IS-A, and a list can have duplicate items, set cannot so it is NOT is-a
 *      - Use composition of the list inside the set instead
 *          - This would be an implemention domain use of composition
 *      
 *          
 * 
 * SUMMARY:
 *  - Composition means something very different than public inheritance
 *      - Public Inheritance -> class D is-a class B + more
 *      - Application Domain -> Composition means has a
 *      - Implementation Domain -> Composition means is implemented in terms off
 */

#include <string>

namespace item38
{
    class Address{};
    class PhoneNumber{};
    struct Person
    {
        std::string name;   // Composition
        Address add;        // ditto
        PhoneNumber number; // ditto
    };
}
