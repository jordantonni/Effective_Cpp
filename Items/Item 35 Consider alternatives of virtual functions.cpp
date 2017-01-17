/*
 * Consider alternatives to virtual functions
 * 
 * Virtual function specifices that:
 *  - There is a default way to do this function, for all classes in the hierarchy
 *  - You can specialize it if you wish
 *  
 * Template Method Pattern | Via Non-Virtual Interface (NVI) Idiom
 *  - Vitual method is private
 *  - Public non virtual wrapper method invokes the virtual one
 *  - Allows derived classes to still override the virtual method, even though it is private
 *      - They can specialize it, just can't choose when it is invoked
 *  - Why?
 *      - The wrapper that is non virtual specified when it is called and ensures other stuff is done in the wrapping code
 *      - The private virtual function is still able to be overriden, so specialization can occur
 *  
 * Strategy Pattern | Via function pointer / Object
 *  - Instead of virtual functions, we have a function pointer or std::function member variable
 *  - Pass in the function we want to ctor
 *  - Non virtual forwarding function just invokes the function pointer
 *  - Why?
 *      - Allows different instances of the same type to have different implementations (unline virtual functions where all objects of same type have same imp)
 *      - Can switch function pointer to at runtime     
 *  - Downside?
 *      - Functions pointed to are not member functions, so they need access to internals usually. Either via friend or getters and setters
 *      
 *  - std::function: Can point to free functions, member functions and function objects
 *      - std::bind allows you to bind another object to a member function of same object, passing itself as *this pointer
 *          -> Allowing you to call member functions of other objects in your own object!
 *
 * Strategy Pattern:
 *  - Hierarchy for your types
 *  - Hierarchy for your types that contain a virtual method to call
 *  - Allows your first types to have a pointer to the second hierarchy and call different implementations of the method that is virtual in them
 * 
 */

namespace item35
{
    //Classic Strategy
    class GameChar;

    class HealthCalc // Base for the strategy classes
    {
    public:
        virtual int calc_health(const GameChar& gc) const = 0;
    };

    class GameChar // Base for the users of the strategy classes
    {
    protected:
        HealthCalc* hc; //Pointer to base of strategy allows for polymorhpic use of them
    public:
        virtual int health() const
        {
            return 100;
        }
    };

    class FastHealth : public HealthCalc
    {
    public:
        virtual int calc_Health(const GameChar& gc) const
        {
            return gc.health() - 10;
        }
    };

    class GoodGuy : public GameChar
    {
    public:
        int health() const
        {
            return hc->calc_health(*this); // Invoke whatever strategy class we point to
        }
    };
}
