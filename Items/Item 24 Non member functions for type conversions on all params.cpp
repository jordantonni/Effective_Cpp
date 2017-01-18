/*
 * Declare functions that require all parameters undergo type conversion, as non-member functions 
 * 
 * 
 * Non explict ctor with either 1 parameter or all having default values is an implicit conversion operator
 *  - i.e. Type(int a = 1, int b = 2) 
 *      - Provides an implcit conversion from a single int to an object of type Type
 *      
 * operator*(Type& rhs) - Multiples 2 Types together, the lhs is the this pointer
 *  - Can be called like:
 *      - Type x = Type(a) * Type(b);
 *      - Type x = Type(a) * 100; // uses the implicit conversion ctor on 100
 * 
 *  NOTE: Implicit conversion ONLY works on parameters, not on the this pointer passed to member functions.
 *  
 *  If you need implicit conversions of all parameters, including what would otherwise be the this pointer, use non-member functions
 *  i.e. operator*, operator+ etc etc
 */

namespace item24
{
    class Rational
    {
        int num, den;
    public:
        Rational(int n = 0 , int d = 1)
            : num{ n }
            , den{ d }
        {}

        int numerator() const
        {
            return num;
        }

        int denominator() const
        {
            return den;
        }
    };

    /*
     * Non-member function, allows for implicit type conversion of lhs and rhs
     */
    const Rational operator*(const Rational& lhs, const Rational& rhs)
    {
        return (lhs.numerator() * rhs.numerator(),
                lhs.denominator() * rhs.denominator());
    }
}
