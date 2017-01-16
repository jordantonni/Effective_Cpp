/*
 *Differentiate between inheritance of interface and inheritance of implementation
 *
 * Precisely specify what dervied classes inherit
 *  - Pure Virtual -> Interface only
 *  - Virtual      -> Interface + Default implementation (can specialize and change)
 *  - Non-Virtual  -> Interface + Mandatory implementation (can't change)
 */

#include <iostream>
using namespace std;

namespace item34
{
    class base
    {
    public:
        virtual void draw() = 0;

        void print()
        {
            cout << "base" << endl;
        }
    };

    class d : public base
    {
    public:
        void draw() override
        {
            int x;
        }

                void print()
                {
                    cout << "der" << endl;
                }
    };

    void base::draw()
    {
        std::cout << "hehe" << std::endl;
    }


    void test()
    {
        d x;
        base* bp = &x;
        d* dp = &x;

        bp->print();
        dp->print();
    }
}
