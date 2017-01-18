/*
 * Factor parameter-independent code out of templates
 * 
 * Code replication is implicit in templates and hard to see. Remember that templates are instantiated / Stamped out
 * for each different template parameter passed to it.
 * 
 * Template Parameters:
 *  - Type Parameter: <typename T>
 *  - Non-Type Parameter: <int n> or <size_t n>
 *  
 * Factor out non-type parameters if you can. As each difference in them would instantiate a new template. 
 *
 *
 * SUMMARY:
 *  - Any code in a template not dependent on a template paramter leads to code bloat
 *  - Replace template non-type paramters with function parameters or class members
 *  - Bloat due to Type parameters can sometimes be reduced via using types that are compatiable with each other (int*, long* -> T*)
 */

#include <iostream>

namespace item44_bad
{
    template <typename T, int n>
    class SquareMatrix
    {
        T* data;
    public:
        SquareMatrix(T* da)
            : data { da }
        {}

        void zero();
    };

    template <typename T, int n>
    void SquareMatrix<T, n>::zero()
    {
        // Zero all the elements in the matrix pointed to by T* mat
        for (int i = 0; i < n; ++i)
        {
            data[i] = 0;
        }
    }

    void print(int* data, int size)
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << data[i] << ", ";
        }
        std::cout << std::endl;
    }

    void test()
    {
        int array1[5] = { 1,2,3,4,5 };
        int array2[10] = { 1,2,3,4,5,6,7,8,9,10 };
        SquareMatrix<int, 5> sm1(array1);
        SquareMatrix<int, 10> sm2(array2);

        print(array1, 5);
        print(array2, 10);
        sm1.zero();
        sm2.zero(); // Would instantiate 2 different versions of SquareMatrix::zero() due to the method being parameterized on size also
        print(array1, 5);
        print(array2, 10);
    }
}

namespace item44_good
{
    template <typename T>
    class SquareMatrixBase
    {
        T* data;
        int size;
    protected:
        void zero();
    public:
        SquareMatrixBase(T* pData, int size)
            : data { pData }
            , size { size }
        {}
    };

    template <typename T>
    void SquareMatrixBase<T>::zero()
    {
        for (int i = 0; i < size; ++i)
        {
            data[i] = 0;
        }
    }

    template <typename T, int n>
    class SquareMatrix : private SquareMatrixBase<T>
    {
    private:
//        using SquareMatrixBase<T>::zero;
    public:
        SquareMatrix(T* data)
            : SquareMatrixBase<T>(data, n)
        {}

        void zero()
        {
            SquareMatrixBase<T>::zero(); 
        }
    };

    void test()
    {
        int array1[5] = { 1,2,3,4,5 };
        int array2[10] = { 1,2,3,4,5,6,7,8,9,10 };
        SquareMatrix<int, 5> sm1(array1);
        SquareMatrix<int, 10> sm2(array2);

        item44_bad::print(array1, 5);
        item44_bad::print(array2, 10);
        sm1.zero(); // No longer instantiates two different versions of Zero() as we moved the template parameter to the dervived class
        sm2.zero(); // and passed it to the zero method as a normal function param
        item44_bad::print(array1, 5);
        item44_bad::print(array2, 10);
    }
}
