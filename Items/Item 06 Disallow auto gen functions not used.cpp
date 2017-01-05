/*
 * Explicitly DISALLOW the use of compiler generated methods that you DONT want
 * 
 * 
 * If you don't want a class to be copied, declare its copy ctor and copy assingment operator private with no implmentation
 * (Note: Can declare as delete in > c++11)
 * 
 * Can also use the Uncopyable base class idiom. 
 * (Note: Not needed in modern c++ due to same reason as above)
 * 
 */

namespace item06
{
    class HomeForSale
    {
    public:
        // ...
    private:
        // Stops other classes from being able to copy this type
        HomeForSale(const HomeForSale&);
        HomeForSale& operator=(const HomeForSale&);
    };

    // Uncopyable base class to stop copying and move link error of trying up to compile time error

    class Uncopyable
    {
    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator&(const Uncopyable&);
    };

    class Home : Uncopyable
    {
        /*
         * This class can not be copied as any attempt will make the compiler try to create the default
         * copy ctor and copy assingment operator, which in turn will try to call the base versions, that we haven't defined.
         * 
         */
    };
}
