/*
 * Understand the behavior of the new-handler
 * 
 * If operator new cannot allocate memory requested, it throws bad_alloc exception, before it does it calls a handler function.
 *  - new_handler: Function that is called when new can't allocate memory
 *  std::new_handler is a typedef for a void function
 *  
 * std::set_new_handler
 *  - Function that sets what the new_handler function should be
 *  - Returns old one
 *  
 * Have class specific new_handler called when objects of it's type are new'd
 *  - set_new_handler function in the class
 *      - Stores the function to use as the handler in the classes own new_handler object
 *  - new_handler object in the class
 *      - Stores the function to call as the handler
 *  - operator new in the class
 *      - Sets the global std::new_handler the one defined for the class, via std::set_new_handler
 *      - Allocates new memory
 *      - RAII class that stores the old handler resets it to the original default one
 *      
 * To get this functionality easily for any class we can use mixin-inheritance
 *  - Mixin -> Base classes that define how to do some type of functionality
 *          -> Can be inherited or use in another class in a modular fashion 
 *  - Using Curiously Recurring Template Pattern (CRTP)
 *      -> Define all the class new_handler stuff above in a templated base class
 *      -> Your own class can inherit from that type, passing itself as the template param
 *          -> Results in each type getting its own version of the mixin base class, -> their own version with specific currentHandler per type
 *          -> Think of CRTP as saying "Do it for me", do this functionality for my type, by specifying type as a param
 *
 * SUMMARY
 *  - set_new_handler allows you to specify a void function that gets invoked when operator new can't allocate memory
 *  - Can override this and operator new as shown to set a specific hander per user defined type
 *  - Curiously Recurring Template Pattern allows for easy Mixin-Inheritance
 *      -> Allows you to provide this functionality to any class easily
 */

#include <new>
#include <iostream>

namespace item49
{
    void outOfMem()
    {
        std::cout << "OH FUG" << std::endl;
        std::abort();
    }

    // ********************* Class specific new handler ********************************

    // NewHandlerHolder will provide RAII idiom to store and then reset the global new_handler to default
    class NewHandlerHolder
    {
    public:
        explicit NewHandlerHolder(std::new_handler new_handler) //Store a new_handler function
            : handler{ new_handler }
        {}

        ~NewHandlerHolder()
        {
            std::set_new_handler(handler); // Restore the global new_handler function to what we stored earlier
        }

    private:
        std::new_handler handler;
        NewHandlerHolder(const NewHandlerHolder&);
        NewHandlerHolder& operator=(const NewHandlerHolder&);
    };


    // *********************** Widget class that defines its' own handler *********************

    class Widget
    {
    public:
        static std::new_handler set_new_handler(std::new_handler p) throw(); // The overridden set_new_handler
        static void* operator new(std::size_t size) throw(std::bad_alloc); // The overridden new operator

    private:
        static std::new_handler currentHandler;
    };

    std::new_handler Widget::currentHandler = 0;

    std::new_handler Widget::set_new_handler(std::new_handler p) throw()
    {
        std::new_handler old_handler = currentHandler; // Store previous handler used for this class, null to start
        currentHandler = p; // Make p the new_handler to use for this class hereforth
        return old_handler;
    }

    void* Widget::operator new(std::size_t size) throw(std::bad_alloc)
    {
        NewHandlerHolder h(std::set_new_handler(currentHandler)); // Make the global new_handler use Widgets defined one + store the default one in RAII class.
        return ::operator new(size); // Try and get memory for object as usual and return a point to that new memory.
    } // RAII class NewHandlerHolder is destructed, and the default normal new_handler is reinstated as the global new_handler.


    // ******************** Curiously Recurring Template Pattern *****************************

    template <typename T>
    class NewHandlerSupport
    {
    public:
        static std::new_handler set_new_handler(std::new_handler p) throw()
        {
            std::new_handler old = currentHandler;
            currentHandler = p;
            return old;
        }

        static void* operator new(size_t size) throw (std::bad_alloc)
        {
            NewHandlerHolder(std::set_new_handler(currentHandler));
            return ::operator new(size);
        }

    private:
        static std::new_handler currentHandler;
    };

    template <typename T>
    std::new_handler NewHandlerSupport<T>::currentHandler = 0;

    // To use the CRTP
    class EasierWidget : NewHandlerSupport<EasierWidget>
    {};


    void test()
    {
        //        std::new_handler old = std::set_new_handler(outOfMem);

        //        int* p = new int[100000000L];
        //        int* cp = new int[100000000L];
        //        int* hjfd = new int[100000000L];
        //        int* jfkd = new int[100000000L];  // Not enough memory to call all these, operator new will call the current new_hander, which is outOfMem()

        Widget::set_new_handler(outOfMem); // Set's the new_handler member variable in Widget to be outOfMem function 
        Widget* pw = new Widget;
    }
}
