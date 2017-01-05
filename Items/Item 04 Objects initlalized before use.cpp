/*
 * Ensure objects (primitive variables and user defined types) are initialized before use
 * 
 * Always initialize objects yourself to be sure they are initialized.
 *  C++ only sometimes initializes built-in types. Best to do it always.
 *  
 * Built in types - manually done via assignment
 * classes - use their ctors initializer list
 * 
 * Base classes are initialized before derived
 * Class data members are initialized in the order they are declared -> ENSURE you init them in that same order in the initializer list
 * 
 * Don't have non-local (outside a function) static (lifetime) objects depend on each other for initialization. 
 * The order is undefined.
 * Instead, replace them with singelton functions that create a static instance and return a reference to them.
 */

#include <string>

namespace item04
{
    int x; // initialized to 0

    class point
    {
        int x; // Sometimes initialized sometimes not
    };

    // Difference between initialization and assingment
    class address
    {
        std::string road;
        int number; // Built in type so not guarantee will be initialized or not! Best to do it yourself in init list!
        const double cdoub; // const and references MUST be initialized to compile -> have to in the initializer list!

        address(std::string rd, int num)
            : road{ rd }
            , number { num } // This is initialization!
            , cdoub{ 13.37 }
        {
            // Assignment. C++ dictates that non built-in types are constructed before the ctor body is executed
            // string road is either default ctord or initialized via the initializer list above if provided
            road = "";
            number = 0;
        }

        // Correct way to implement a default ctor that just intiilaizes all memebers to default values
        address()
            : road{}
            , number{ 0 }
            , cdoub{ 13.37 }
        {}
    };

    /*
     * Non-local static objects defined in other translation units
     * 
     * Static -> In this sense refers to LIFETIME. Created not on the heap or the stack, at the start of program, deleted at end of execution.
     * Non-local -> Not belonging to any function.
     * 
     * Problem: All these below objects (apart from the local_static in the function) have no defined order of initialization.
     * Therefore -> Can't use them to initialize each other, as who would come first? Impossible to solve.
     * 
     * Soltuion: If needed, wrap them into singleton pattern where a function creates a static instance and returns reference to them.
     * Use the function, i.e. int val = singleton_object() , instead of int val = object;
     */

    int global_int; // Has static lifetime
    extern int extern_global_int; // Has static lifetime
    static int non_global_int; // Has static lifetime && static scope (Can only been seen in this file, not a global variable)
    void test()
    {
        static int local_static; // Has static lifetime but is LOCAL to the function
    }
    class test_class
    {
        static int class_static; // Has static lifetime
    };
}
