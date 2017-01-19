/*
 * Define non-member functions inside templates when type conversions are desired
 * 
 * (Item 24) Non member functions can provide implicit type conversions between all args - Implicit this pointer doesnt allow it for member f
 * unctions.
 *  - Implicit type conversions like using a non-explicit ctor allow for this
 * 
 * To support this for templated functions we have problems:
 *  - Compiler needs to figure out the types of the arguments passed in, in order to instantiate a function with those types.
 *  - Implicit type conversions are NEVER considered for template argument deduction
 *      -> Meaning, there is no way to convert some type U to a templated<T> using its' ctor, so it can't figure out what to use as T
 * 
 * Class Templates don't require template argument deduction, only function templates do
 *  - Declare the templated functions as a friend 
 *  - Means T is known at compile time
 *  - Templated function is instantiated with the correct T types
 *      -> Meaning, it can now be called with some type U, as long as there is a conversion availble from U to T
 *      - Why? Because the templated function is now an instantiated FUNCTION, not a function template, as implicit conversion works in functions.
 *      
 *      
 * Ensure you define the friend function inside the class also
 *  - This is needed for the linker
 *  
 * Basically!:
 *  - Declaring the function as a friend means the function template is instantiated into a real function with T = Whatever the type is passed in to the 
 *    class when you declared an object of it. i.e. when Rational<int> rat(1,2) was declared, a version of operator* with Rational<int> for everything was made.
 *    As long as there is a conversion from whatever you pass in to the operator* to int in this case, it will work!
 * 
 * SUMMARY:
 *  - If a class template offers functions where all parameters need to be implicity converted, such as operator*,
 *    define those as friends inside the class template
 */


#include <iostream>

namespace item46
{
    template <typename T>
    class Rational
    {
        T num;
        T den;
    public:
        Rational(const T& num = 0, const T& den = 1)
            : num{ num }
            , den{ den }
        {}

        const T numerator() const
        {
            return num;
        }

        const T denominator() const
        {
            return den;
        }

        /*
         * Inside a class template, the name of the template, Rational here, also means Rational<T>
         * 
         * Having it as a friend does two things:
         * 1) Keeps it a non member, allowing item 24 to work, Implicit conversion on all params due to no this pointer
         * 
         * 2) This method is now instantaited for whatever type Rational<TYPE> is given. In this case int.
         *    So the compiler no longer has to guess what type 2 is below, it knows it needs to be converted to a Rational 
         *    and as long as there is a conversion from that type to a rational it will succeed!
         * 
         */
        friend const Rational operator*(const Rational& lhs, const Rational& rhs)
        {
            return Rational(lhs.numerator() * rhs.numerator(),
                            lhs.denominator() * rhs.denominator());
        }
    };

    template <typename T>
    void print(const Rational<T>& rat)
    {
        std::cout << rat.numerator() << "/" << rat.denominator() << std::endl;
    }

    void test()
    {
        Rational<int> r1(1, 2);
        Rational<int> r2(1, 4);


        Rational<int> result = r1 * 2;

        print(result);
    }
}
