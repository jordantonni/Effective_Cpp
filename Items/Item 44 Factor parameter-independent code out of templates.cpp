/*
 *
 *
 * SUMMARY:
 *  -
 */

#include <iostream>

namespace item44_bad
{
    template <typename T, int n>
    class SquareMatrix
    {
    public:
        SquareMatrix()
        {}

        void zero();
    };

    template <typename T, int n>
    void SquareMatrix<T, n>::zero()
    {
        int x; // Zero all the elements in the matrix pointed to by T* mat
    }

    void test()
    {
        //        SquareMatrix<int, 5> sm1;
        //        SquareMatrix<int, 10> sm2;
        //        sm1.zero();
        //        sm2.zero(); // Would instantiate 2 different versions of SquareMatrix::zero() -> Code Bloat
    }
}

namespace item44_good
{
    template <typename T>
    class SquareMatrixBase
    {
    protected:
        void zero(int size);
    };

    template <typename T>
    void SquareMatrixBase<T>::zero(int size)
    {
        int x; // Do work
    }

    template <typename T, int n>
    class SquareMatrix : private SquareMatrixBase<T>
    {
    private:
        using SquareMatrixBase<T>::zero;

    public:
        void zero()
        {
            zero(n); // Inline invocation to base version passing the size as a parameter now.
            // Means no method call cost due to inline (zero() body is just pasted here)
        }
    };
}
