/*
 * Provide a way to get the raw resource from a resource-managing class
 * 
 * Many APIs need raw pointers to work with. So you need to define a method to get that.
 * 
 * 2 Ways to do this: 
 * 
 * Explicit conversion:
 *  Provide a get() method that returns a pointer to the resource itself.
 *  
 * Implicit conversion:
 *  Override operator* and operator->
 *  Provide a operator RESOURCE_TYPE() implict conversion function.
 *  
 *  Remember:
 *  Best pracise it to only provide explicit conversion. Safer in that it can't be done by accident.
 *  But is more effort to use.
 */

namespace item15
{
    class Resource
    {};

    class ResourceManager
    {
        Resource* resPtr;

    public:
        // Explicit conversion to get underlying resource.
        Resource* get() const
        {
            return resPtr;
        }

        // Dereference overloads to the underlying object
        Resource& operator*() const
        {
            return *resPtr;
        }

        Resource& operator->() const
        {
            return *resPtr;
        }

        // Implicit conversion
        operator Resource() const
        {
            return *resPtr;
        }
    };
}
