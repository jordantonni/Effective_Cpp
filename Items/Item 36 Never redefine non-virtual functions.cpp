/*
 * Never redefine inherited non-virtual functions
 * 
 * Non-Virtual functions are statically bound to the type of your object.
 * What does that mean?
 *  - If you have a pointer to a Base type that points to a Dervied type
 *      - Static type of the pointer is BASE
 *      - Dynamic type of the pointer is DERIVED (Note the dynamic type can change depending on what it points to)
 * 
 * 
 * This means non-virtual methods will be statically bound to the type of your objects and in the case above that is BASE
 *  -> Calling a non-virtual method on a pointer to base will call the BASE method, not the derived
 *  
 *  Note: If you have a dervied pointer it would call the derived method. Base pointer would call base method.
 *      - Regardless of what was really pointed to (Dynamic Type)
 *
 *    
 *  SUMMARY:
 *      - Never override a non-virtual method
 */

namespace item36
{
    class Base
    {
    public:
        void mf()
        {}
    };

    class Derived : public Base
    {
    public:
        void mf()
        {}
    };

    void test()
    {
        Derived d;
        Base* bp = &d; // Static type = Base, Dynamic Type = Derived
        Derived* dp = &d; // Static type = Derived, Dynamic Type = Derived

        bp->mf(); // Invokes static bound non virtual function -> Base::mf()

        dp->mf(); // Invokes static bound non virtual function -> Dervied::mf()
    }
}
