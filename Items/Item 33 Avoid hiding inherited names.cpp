/*
 * Avoid hiding inherited names
 * 
 * 
 * Names in derived class will hide names in base
 *  - NEVER want you want in public inheritance
 *  
 * Derived class scope is actually nested inside the Base class scope. 
 *  
 *  
 * Name hiding works on the name itself, not on the signiture
 *  - If you have multiple Overloaded functions in base
 *      - ALL of them will be hidden if any function has same name in derived
 *  - Overcome this by either having a using declartation of Base::MethodName(); to bring them back into scope
 *  
 * In public inheritance, you are modelling an IS-A relationship
 *  -> You must ensure you inherit overloads from base classes, else you are violating this principle
 *  
 *  SUMMARY:
 *  - Names in dervied classes hide all the names in the base, including all the overrides. Never what you want in public inheritance
 *  - Bring hidden names back in scope via:
 *      - Using declarations
 *      - Forwarding functions that invoke Base::func() within their body
 */

namespace item33
{
    class Base
    {
    private:
        int x;
    public:
        virtual void mf1() = 0;
        virtual void mf1(int);

        virtual void mf2();

        virtual void mf3();
        virtual void mf3(double);
    };

    class Derived : public Base
    {
    public:
        virtual void mf1(); // Hides the int version in base
        void mf3(); // Hides both mf3s in the base, so calling via Derived.mf3(3.4) would have a compilation error, even though a double version is in base!
        void mf4();
    };


    class CorrectDerived : public Base
    {
    public:
        using Base::mf1; // This ensures the below overrides of mf1 and mf3 only override the same function signiture as in base
        using Base::mf3; // and allows the mf1(int) and mf3(double) from base to be called correctly!


        virtual void mf1();
        void mf3();
        void mf4();
    };
}
