/*
 * Copy all parts of an object
 * 
 * Well designed class should only have 2 function that copy and object.
 * Copy ctor, copy assignment operator.
 * 
 * If you create your own copy ctor / assingment op you are replacing the compiler generated default ones (saying I need them done differently)
 * 
 * If you add new data memebers, you need to update all these copy ctor, copy assignment op and any other assignment op. No warnings will be shown.
 * else you will only do a partial copy. Bad!
 * 
 * Ensure when you write you copy constructor and copy assignment operator that you
 * 
 * 1) Copy ALL data members in the class
 * 2) Invoke the copy ctor of the base class
 * 3) Invoke the copy assignment operator of base class in copy assingment operator
 * 
 *  DO NOT USE copy ctor in copy assignment op or vice versa, it makes no sense to do so!
 *  
 *  Instead you can encapsualte common copying functionality into a third private function and invoke it from
 *  the copy ctor and copy assignment op
 */


#include <string>

namespace item12
{
    class Customer
    {
        std::string name;
        int salary;

    public:
        Customer(const std::string& name, const int salary)
            : name { name }
            , salary { salary }
        {}

        /*
         * Ensure both copy ctor and copy assingment operator copy ALL memeber variables
         */
        Customer(const Customer& rhs)
            : name { rhs.name }
            , salary { rhs.salary }
        {}

        Customer& operator=(const Customer& rhs)
        {
            name = rhs.name;
            salary = rhs.salary;
        }
    };


    class VipCustomer : public Customer
    {
        int priority;

    public:
        VipCustomer(const int priority, const std::string name, const int salary)
            : Customer { name, salary }
            , priority { priority }
        {}

        /*
         * Ensure we invoke the base class copy ctor and assignment operator components from the derived class counter parts!
         */
        VipCustomer(const VipCustomer& rhs)
            : Customer { rhs } // Call base copy ctor
            , priority { rhs.priority }
        {}

        VipCustomer& operator=(const VipCustomer& rhs)
        {
            Customer::operator=(rhs); // Call base copy assingment
            priority = rhs.priority;

            return *this;
        }
    };
}
