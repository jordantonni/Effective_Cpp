/*
 * Use const whenever possible
 *
 * Bitwise const - Data memebers of the class arent modified in any way (but data pointed to by memeber pointer could be) How c++ compiler
 *                 enforces const.
 * Logical const - Idea that nothing should be changed though a const memeber method. Including data a memeber pointer points to.
 * 
 * Compilers enforce bitwise const, but I should program using logical constness
 *
 * If const and non const methods have same implementations. Call the const from the non const using casts.
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
        mutable int text_length; // Mutable allows this field to be modified even in a const method!

        // Needs to return a reference otherwise wouldnt be able to write to the actual value in the string, would get a copy instead!
        // Also functions return by value. So you would be assigning to an r-value (illegal) if you wrote to it!
        // Note how we use the definition of LOGICAL constness, we are changing a memeber field, text_length, but for all intents and purposes, it is a const function.
        const char& operator[](const std::size_t index) const
        {
            text_length = text.length();
            return text[index];
        }

        char& operator[](const std::size_t index)
        {
            text_length = text.length();
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

    /*
     * Avoiding code duplication using const casts
     * 
     * If you have const and non const versions of methods to ensure both const and non const objects can call them
     * you can end up with code duplication. Calling the const version from the non const can help.
     * 
     * NOTE: Never call the non const from the const (via removing the const with a const_cast) as that would allow 
     * the objects' internal state to be modified. 
     */

    class anotherTextBlock
    {
        std::string text;

        const char& operator[](const int position) const
        {
            return text[position];
        }

        // Cast itself *this to a const version of itself, call the const operator[] 
        // remove const and return it
        char& operator[](const int position)
        {
            return const_cast<char&>(
                static_cast<const anotherTextBlock&>(*this)[position]
            );
        }
    };
}
