/*
 *
 */

#include <iostream>
using namespace std;


namespace item40
{
    class Borrowable
    {
    public:
        void checkOut()
        {
            cout << "borr chec" << endl;
        }
    };


    class ElectronicGadget :public Borrowable
    {
    private:
        void checkOut() const
        {
            cout << "der const check" << endl;
        }
    };


    void test()
    {
        ElectronicGadget g;
    }
}