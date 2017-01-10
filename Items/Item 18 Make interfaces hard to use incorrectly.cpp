/*
 * Make Interfaces easy to use correctly and hard to use incorrectly
 * 
 * 
 * Use types (define new classes) to enforce correct parameters
 *  i.e. instead of int as parameter define a new type to represent better what that int is; Enum Class is perfect for this
 *       Restrict possible values of new Type.
 * 
 * Make your own Types behave exactly as built in types do. Unless you have good reason.
 *  i.e. Have operator*() return a const value, to stop the result from being a valid l-value
 * 
 * Be consistent
 *  i.e. In C#, Arrays have a property Length, but ArrayLists have property called Count -> BAD and inconsistent
 *  
 * Don't rely on the client of your Interface to have to remember to do something, like free some memory
 *  i.e. return a smart pointer instead of a raw pointer to some heap allocated resource
 *  
 * Avoid Cross DLL problem
 *  Object new'd in DLL A has to be delete'd in DLL A, else runtime errors occur
 *  smart pointers, such as shared_ptr, have their default deleter call delete from the same DLL it was new'd in
 */

#include <memory>

namespace item18
{
    class Resource
    {
    public:
        static void close();
    };

    //BAD - Client has to remember to free resource
    //    - Also has to know not to use delete to free it, but call it's close method
    Resource* getResource()
    {
        return new Resource;
    }

    void testBad()
    {
        Resource* rPtr = getResource();
        // delete rPtr // This isnt how to free the resource in this case
    }

    //GOOD - Interface takes care of freeing resouce correctly, without client having to do anything
    std::shared_ptr<Resource> getRes()
    {
        return std::shared_ptr<Resource>(new Resource, Resource::close);
    }
}
