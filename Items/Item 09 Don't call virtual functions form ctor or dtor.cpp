/*
 * Never call virtual functions during construction and destruction
 * 
 * During construction of a dervied class, the object first has to construct the base class.
 * During this time, the type of the object IS OF TYPE BASE.
 * -> Only becomes derived type once the derived ctor is running.
 * 
 * All parts of c++ that care about an objects type, i.e. typeof, dynamic_cast etc will see the object as a base, not as a derived.
 * 
 * So virtual function calls during construction will only call the method in that class, as the more derived type doesnt exist yet.
 * 
 * Same for destructors: after derived dtor has run, object is now a base type, so virtual calls wont go down to derived
 * 
 * TLDR: Virtual function calls during construction or destruction will never leave the currently ctor / dtor class
 * 
 */

#include <string>

namespace item09
{
    // BAD
    class Transaction
    {
    public:
        Transaction()
        {
            init(); // BAD - ctor is calling init, which in turn is calling a VIRTUAL function during construction.
        }

        void init()
        {
            logTransaction();
        }

        virtual void logTransaction()
        {};
    };

    // GOOD solution
    // How to get differetn behavior without using virtual functions in ctor?
    // Instead of calling down using virtual mechanism, pass values up

    class SoltuionTransaction
    {
    public:
        SoltuionTransaction(const std::string& logInfo)
        {
            logTransaction(logInfo);
        }

        void logTransaction(const std::string& logInfo)
        { }
    };

    class DervivedTransaction : public SoltuionTransaction
    {
    public:
        DervivedTransaction(int SomeMoreParametersHere, const std::string& logInfo)
            : SoltuionTransaction{ logInfo }
        {
            // ... ^^ Note we pass the log info to the base ctor, this way we get Derived specific data used in the base ctor without using virtual methods!
        }
    };
}
