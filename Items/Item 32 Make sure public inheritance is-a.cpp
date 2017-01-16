/*
 * Make sure public inheritance models "is-a" relationship
 * 
 * Public inheritance means "is-a"
 * 
 * class D : public B   - Tells C++ Compiler that EVERY D is also a B and that D can ALWAYS be used where a B can be used
 *                      - Only true for public inheritance
 *  - B is more general than D
 *  - D is more specialized than B
 *  
 * In order to use public inheritance correctly you must ensure that the derived class really is-a base
 *  - Square is NOT a rectangle, why?
 *      - If base rectangle has a change width method, but that only changes the width data memeber
 *      - Square would also change the hight, that would mean square has a different invariant than rectangle
 * 
 * SUMMARY:
 *  Everything that appliees to base must also apply to the dervied in public is-a inheritance
 * 
 */

namespace item32
{
    class Person
    { };

    class Student : public Person
    { };

    void eat(const Person& p)
    {}

    void study(const Student& s)
    {}

    void test()
    {
        Person p;
        Student s;

        eat(p); // Works as a student IS-A person
        eat(s);

        study(s);
        // study(p);    - Fails as Person IS NOT a Student

    }
}
