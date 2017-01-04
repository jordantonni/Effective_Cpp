#include <iostream>

namespace intro
{
    /* Declarations:
     * Lets compiler know about existence of some object or construct 
     */
    extern int x; // No memory set aside
    std::size_t method(int num); // Signiture: Defines the type of the function. Return type + Parameters
    class Widget;

    template <typename T>
    class Node;


    /* Definitions:
     * Gives compiler the details.
     * For objects -> sets aside memory
     * For functions and classes -> provies the implementation and members
     */
    int x; // Sets aside memory

    std::size_t method(int num)
    {
        return num * 4;
    }

    class Widget
    {
    public:
        Widget();
        Widget(const Widget& rhs); // Copy ctor (Initializses a new Widget from another one)
        Widget& operator=(const Widget& rhs); // Copy assingment operator (Copies value from another one into already existing Widget)
        ~Widget();
    };

    // = can also invoke copy ctor
    Widget w1;
    Widget w2 = w1; // Will incoke copy ctor, not assingment as w2 is being created for first time here.

    template <typename T>
    class Node
    {
        T value;
    };

    /* Initialization:
     * Giving object it's first value. Done via ctor for classes and structs
     */

    class A
    {
        A(); // Default ctor
    };

    class B
    {
        explicit B(int x = 1); // Also default ctor (can be called with no args) 
        // Explicit ensures can't convert int to B without using B(val)
    };

    class C
    {
        C(int x); // Not default ctor
    };
}
