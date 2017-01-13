/*
 *
 * Precisely specify what dervied classes inherit
 *  - Pure Virtual -> Interface only
 *  - Virtual      -> Interface + Default implementation
 *  - Non-Virtual  -> Interface + Mandatory implementation
 */

#include <iostream>
using namespace std;

namespace item34
{
    class base
    {
    public:
        virtual void draw() = 0;
    };

    class d : public base
    {
    public:
        void draw() override
        {
            int x;
        }
    };

    void base::draw()
    {
        std::cout << "hehe" << std::endl;
    }

    void test()
    {
        base* p = new d;
        p->draw();
        p->base::draw();
    }
}
