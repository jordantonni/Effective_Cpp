/*
 * Declare destructors virtual in polymorphic base classes
 * 
 * Not declaring the base destructor virtual in a hierarchial class tree means a base pointer holding a reference to a
 * derived type will only call the base destructor -> resulting in a partially destructed object and a resource leak!
 * 
 * Virtual functions require extra meta information within the class, such as:
 *  virtual table pointer , vptr
 *  virtual table, vtable
 *  Resulting in:
 *      More memory for the class
 *      Longer time to invoke function
 *      Not compatiable with other language such as C etc, as now your object has c++ specific virtual meta data in it.
 *      
 *  Classes such as std::string, stl containers etc don't have a virtual destructor, therefore you SHOULD NOT inherit from them.
 *      i.e. Don't be tempted to make a superString class that inherits from string (Java & c++ have final, sealed keywords to stop this inheritance)
 *
 * If you want to make an abstract class (A class that can't be instantiated, has at least 1 pure virtual function, used for a base)
 * You can declare the destructor pure virtual:
 *  - virtual ~AbsBase() = 0;
 * Must define pure virtual dtor, e.g. for above AbsBase::~AbsBase() {}
 * Why? dtors are called from most derived -> base, Compiler will generate call to base dtor from dervived ones. If no body exists then linker error!
 *  
 * Solution: Any class with virtual functions should have a virtual destructor.
 *           Classes that are not to be polymorphic or as a base class should NOT have virtual destructors, as it adds to their size.
 */


namespace item07
{
    class TimeKeeper
    {
    public:
        int x;

        explicit TimeKeeper()
        {};

        // Virtual destructor ensures more derived class destructor will be called and clean up its class also
        virtual ~TimeKeeper()
        {};
    };

    class AtomicTime : public TimeKeeper
    {
        int y; // Without a virtual base dtor, this int wouldnt be cleaned up if called from a TimeKeeper* pointer.

        ~AtomicTime()
        {}
    };

    // Pure virtual class by means of a pure virtual dtor // Note we define the dtor also for reason explained above
    class AWOL
    {
    public:
        virtual ~AWOL() = 0;
    };

    AWOL::~AWOL()
    { }
}
