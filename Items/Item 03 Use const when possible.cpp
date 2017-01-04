/*
 * Use const whenever possible
 *
 * Bitwise const - Data memebers of the class arent modified in any way (but data pointed to by memeber pointer could be) How c++ compiler
 *                 enforces const.
 * Logical const - Idea that nothing should be changed though a const memeber method. Including data a memeber pointer points to.
 */

#include <vector>
#include <iostream>

namespace item03
{
    /*
     * const with objects
     */
    int x;
    const int* p; // pointer to const int data
    int* const cp = &x; // const pointer to int data
    const int* const cpc = &x; // Const pointer to const data

    void f1(const int x);
    void f2(int const x); // Both take const int param, order doesnt matter

    const std::vector<int>::iterator it; // Akin to T* const, the iterator itself is const, not the data
    std::vector<int>::const_iterator cit; // The data itself is const

    /*
     * Functions
     *
     * Returning const from a function can stop things like (a*b) = c; if operator* within typeof(a) is non const that would be valid.
     *
     * const member functions define the interface that can be used on const objects, important as you want to use
     * pass by refernce to const as much as possible for efficiency. Only possible if you have const methods that you want to call.
     *
     * you CAN overload on defining a method as const (just not only on the return type being const)
     *
     */

    struct textBlock
    {
        std::string text;

        // Needs to return a reference otherwise wouldnt be able to write to the actual value in the string, would get a copy instead!
        // Also functions return by value. So you would be assigning to an r-value (illegal) if you wrote to it!
        const char& operator[](const std::size_t index) const
        {
            return text[index];
        }

        char& operator[](const std::size_t index)
        {
            return text[index];
        }
    };

    textBlock tb { "Hello" };
    const textBlock ctb { "World" };

    void test()
    {
        std::cout << tb[2] << std::endl; // operator[] non-const
        std::cout << ctb[2] << std::endl; // operator[] const
    }

    void test2(const textBlock& tb)
    {
        char val = tb[2]; // Can only work if textBlock has a const operator[], due to being passed in as a const ref
    }
}
