/*
 * Be aware of Template Metaprogramming
 * 
 * Code that executes and computes during compilation.
 * 
 * Loops are done via recursion of template instantiation
 *  - Instantiating another version of the template within itself, with different paramter values
 * 
 * 
 * SUMMARY:
 *  - Can shift work from runtime to compile time -> Earlier error detection
 */


#include <iostream>

namespace item48
{
    template <unsigned N>
    struct Factorial
    {
        /*
         * Recursively instantiates new Factorial structs, each with their own value for value
         */
        enum
        {
            value = N * Factorial<N - 1>::value
        };
    };

    // Base case terminating condition
    template <>
    struct Factorial<0>
    {
        enum
        {
            value = 1
        };
    };

    void test()
    {
        std::cout << Factorial<10>::value << std::endl;
    }
}
