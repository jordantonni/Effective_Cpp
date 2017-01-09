/*
 * Prevent exceptions from leaving destructors
 * 
 * If a dtor throws an unmanaged exception, c++ undefined behaviour occurs!
 * 
 * If you have code in dtor that can throw an exception:
 * 2 ways to fix:
 *  1 - Try block in dtor, catch and terminate program -> Good option if the program would be unable to continue after exception.
 *  2 - Try block in dtor, catch and swallow -> Only applicable if the program could continure correctly even after exception.
 *  
 *  Best solution:
 *  
 * 
 */

#include <vector>

namespace item08
{
    class Widget
    {
    public:
        // ...
        ~Widget()
        {
            // ...
        }
    };

    void doSomething()
    {
        std::vector<Widget> v;
    } // v destroyed here, if first Widget in v dtor thows exception, all others will be destroyed -> Resource leaks!
}
