/*
 * Postpone variable definitions as long as possible
 * 
 * Unused variables have a cost
 *  - you pay for the construction when control reaches the definition.
 *  - you pay for the destruction when control leaves its' scope.  
 *  
 * Define a variable right before you use it AND can initialize it with the values you want
 *  - This cuts out the default ctor + assignment operator.
 * 
 * In a loop:
 * - Prefer defining the variable INSIDE the loop, it keep's the scope of the varible smaller
 * - UNLESS:
 *  - Objects ctor / dtor pair is much more expensive than assignment operator
 *  - You are in a bottleneck area of performance code
 *  
 *  Note: Define in a loop       -> n ctor + n dtor
 *        Define outside of loop -> 1 ctor + 1 dtor + n assignment operators
 *  
 * 
 * 
 */

#include <string>

namespace item26
{
    std::string encryptPassword(const std::string& s)
    {
        if (s.length() < 10)
        {
            // Throw some logic error
        }

        std::string encrypted(s); // By defining after the check, we ensure we only create string when needed + initilize it with s

        //encrypt(encrypted)
        return encrypted;
    }

    class Widget
    {};

    void loopTest()
    {
        /*
         * Preferable if w's ctor / dtor arent much more expensive than Widgets assignment operator
         * Keeps scope clean
         */
        for (int i = 0; i < 100; ++i)
        {
            Widget w;
        }

        /*
         * Only of cost of Widgets ctor / dtor pair are > expensive than Widgets assignment operator
         */
        Widget w;
        for (int i = 0; i < 100; ++i)
        {
            // use w
        }
    }
}
