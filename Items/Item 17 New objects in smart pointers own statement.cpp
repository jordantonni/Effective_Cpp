/*
 * Store new'ed objects in smart pointer ctor expressions as their own statement.
 * 
 *  Why?
 *  Creation of the new Widget in the shared_ptr consisits of:
 *      1 - Execution of new Widget to allocate the memory and initialize the Widget using its' ctor
 *      2 - Invocation of the shared_ptr ctor, passing in the newly initialized widget.
 *      
 * In C++ function arguments are not defined to be executed in any order. So a possible ordering for below is:
 *  1 - Call new widget
 *  2 - Call Pritory
 *  3 - Call shared_ptr<Widget> ctor
 *  
 *  NOTE: If Priority() throws an exception, the new widget in step 1 is leaked! as #3 will never be exectued so the memeory wont be "managed" by the smart pointer.
 *  
 *  **** I think make_shared, make_unique render this point invalid now, check!
 */

#include <memory>

namespace item17
{
    class Widget{};

    void processWidget(std::shared_ptr<Widget> sp, int priority);

    int getPriority()
    {
        return 1337;
    }

    void test()
    {
        /*
         * BAD
         */
        processWidget(std::shared_ptr<Widget>(new Widget), getPriority());

        /*
         * GOOD
         */
        std::shared_ptr<Widget> pWid(new Widget); // As it's own statement
        processWidget(pWid, getPriority());
    }
}
