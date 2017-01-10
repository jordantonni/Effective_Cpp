/*
 * Consider support for a non-throwing swap method
 * 
 * 
 * Non Templated Class:
 *  (1) - Create efficient public method swap, as it will have access to private fields. (This can call std::swap to do the swapping of the pointers)
 *      - Should NOT throw an exception (Should only swap built in types, and operations on built in types dont throw)
 *
 *  (2) - Declare a non-member T specific swap that calls efficient memeber method swap in same namespace as the Class
 *           -NOT in std namespace
 *  
 *  (3) - Totaly specialize std::swap with your type, invoking your new ^^ efficient member swap via: a.swap(b)
 *          template<>
 *          void swap <Widget> () {}
 *  
 *  
 * Templated Class:
 * 
 *  (1) SAME AS ABOVE
 *  
 *  (2) SAME AS ABOVE
 *  
 *  (3) - Can no longer totally specialize std::swap, need to partially specialize only on Widget, leaving T to be anything we are puting inside Widget!
 *          template <typename T>
 *          void swap <Widget<T>> () {} 
 *      - Not allowed to partially specialize a function, only a class.
 *  
 *  Extra Notes:
 *      ADL - Argument dependent lookup ensures any call to swap will first choose a swap defines in the namesapce of the parameters, which we define in (2)
 *      
 *      We can totally specialize std::swap in the std namespace but can't partially specialize it as it is a function
 *      normal way to get around this is to overload the function but this adds a new function which is not allowed in namespace std.
 *      
 *      Why do we want a good swap anyway?
 *      - Default swap will do a deep copy on objects contaning pointers or using Pimpl which is inefficient as we only need to swap the pointers.
 *      - Swap is used a lot in containers!
 *      
 *      Why non-throwing member swap?
 *      - Strong exception guarantee for classes heavily relies on memeber swap not throwing
 *      - Member swap should only be swapping built in types anyway, and operations on built in types never throw exceptions
 *      
 *      Why using std::swap followed by call to just swap?
 *      - ADL ensures T specific non-member swap will be invoked, which then calls efficient member swap
 *      - If no T specific swap exists, fall back on std::swap, which the using std::swaps brings into play for us
 *      
 *      Why not invoke swap via std::swap()?
 *      - Would not use ADL meaning the non-member T specific swap (2) would not get called, instead std::swap would be
 *      - This is why we totally specialize std::swap when we can ( i.e. when our class isnt templated)
 *          - It ensure even if code wrongly invokes swap via std::swap it will use our specialization of std::swap (3)
 *    
 */

#include <iostream>
#include <string>
using std::cout;
using std::endl;


namespace item25
{
    namespace WidgetStuff // Important as this stops us from polluting the global namespace
    {
        class Resource
        {
            std::string resName;

        public:

            explicit Resource(const std::string& res_name)
                : resName{ res_name }
            {
                cout << "\t\t[" << res_name << "] Resource ctor" << endl;
            }


            Resource(const Resource& other)
                : resName(other.resName)
            {
                cout << "\t\t[" << resName << "] Resource copy ctor" << endl;
            }

            Resource& operator=(const Resource& other)
            {
                if (this == &other)
                    return *this;
                resName = other.resName;
                cout << "\t\t[" << resName << "[Resource copy assignment oeprator" << endl;
                return *this;
            }

            ~Resource()
            {
                cout << "\t\t[" << resName << "]Resource dtor" << endl;
            }
        };

        class Widget
        {
            Resource* res;
            std::string name;
        public:
            explicit Widget(const std::string& n)
                : res { new Resource(n) }
                , name { n }
            {
                cout << "[" << name << "]\t Widget ctor" << endl;
            }

            Widget(const Widget& rhs)
                : res { new Resource(*rhs.res) }
                , name { rhs.name }
            {
                cout << "[" << name << "]\t Widget copy ctor" << endl;
            }

            Widget& operator=(const Widget& rhs)
            {
                Resource* original = res;
                res = new Resource(*rhs.res);
                name = rhs.name;
                delete original;

                cout << "[" << name << "]\t Widget copy assignment operator" << endl;
                return *this;
            }

            ~Widget()
            {
                delete res;
                cout << "[" << name << "]\t Widget dtor" << endl;
            }

            friend std::ostream& operator<<(std::ostream& oss, const Widget& wid)
            {
                return oss << wid.name << endl;
            }

            // Efficient Swap - Swaps the two resource pointers
            void swap(Widget& rhs);
        };


    }
}

/*
 * Ignore the absolute disaster with these namespaces
 * 
 * std::swap has to to be specialized before it is invoked anyway, else the template is already instantiated and compilation fails!
 * 
 * But we need the details of Widget before we specialize std::swap in order to be allowed to call a.swap(b)
 */

namespace std
{
    template <>
    void swap<item25::WidgetStuff::Widget>(item25::WidgetStuff::Widget& a, item25::WidgetStuff::Widget& b)
    {
        a.swap(b);
    }
}

namespace item25
{
    namespace WidgetStuff
    {
        void Widget::swap(Widget& rhs)
        {
            cout << "****** MEMEBER EFFICIENT SWAP ******" << endl;
            using std::swap; // Ensures we can use the built in std swap for the invocations below as a fall back if they dont define their own
            swap(name, rhs.name);
            swap(res, rhs.res);
        }

        // Non-Member swap - ADL ensures when swap is called, this method is invoked which in turn calls the Efficient swap ^^
        void swap(Widget& lhs, Widget& rhs)
        {
            lhs.swap(rhs);
        }

        void test()
        {
            using std::swap;

            Widget a("a"), b("b");

            cout << "\n\nENTERING SWAP" << endl;
            std::swap(a, b);
            cout << "OUTSIDE SWAP\n" << endl;

            cout << "Widget a = " << a << "Widget b = " << b << endl;
        }
    }
}
