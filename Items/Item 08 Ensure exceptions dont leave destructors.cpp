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
 *  Move the possible exception throwing code from dtor into a "close()" method, this allows two things:
 *      1 - Caller can call close() themselves from a try block and handle it how they want if it throws
 *      2 - Dtor checks if close() has been called, if not try call it from dtor anyway. If throws just term or swallow as above
 *   Why?
 *   Allows user to try and handle the dtor stuff themself, if they dont it still gets called from dtor anyway but at least gave user the chance.
 *   
 *   
 * 
 */

#include <vector>

namespace item08
{
    class Widget
    {
    public:
        bool closed;

        void close()
        {
            // Exception throwing code here necessary to close the object
            closed = true;
        }

        // Dtor
        ~Widget()
        {
            if (!closed)
            {
                try
                {
                    close();
                }
                catch(...) {
                    // Log and terminate
                }
            }
        }
    };

    void doSomething()
    {
        std::vector<Widget> v;
    } // v destroyed here, if first Widget in v dtor thows and emits exception, all others will be destroyed -> Resource leaks!
}
