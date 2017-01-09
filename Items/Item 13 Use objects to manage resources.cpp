/*
 * Use objects to manage resources
 * 
 * Resources: Heap memory, DB connection, Network socket, GUI Handle, Mutex lock etc
 * 
 * RAII: Resource Acquisition Is Initialization
 *  - As soon as an object is made on the heap with new, it is immediatly given as initialization to the resource management class.
 *      Either via direct initializion in the ctor.
 *      or via assignment straight after the new.
 *  
 *  Resource managing objects release their resource in their destructor. Ensuring whatever way control left the scope, it will be freed!.
 *  
 *  Use std::shared_ptr<> 
 *  Which is a RCSP (Reference Counting Smart Pointer)
 *  
 *  NOTE: Both auto_ptr and shared_ptr use delete in their dtor
 *  Not delete [] therefore DO NOT CREATE ARRAY of dynimically allocted memory and assign to smart pointer. They will not delete it correctly.
 *  i.e. std::shared_ptr<char> pChar ( new char [1024] ) // This will not be deleted correctly in the dtor!
 *  
 *  Solution: Use String or Vector instead of dynimically allocated char or any other type respectively.
 */


#include <memory>

namespace item13
{
    void bad()
    {
        class investment
        {};

        investment* ptr;
        //...
        delete ptr; // If bad() returns during //.., the ptr is never deleted and resource is leaked. Better to have deletion enfored using stack semantics of dtor.
    }

    /*
     * Depreciated auto_ptr
     * 
     * Deletes resource once ptr itself is destroyed.
     * Can't copy, copying via copy ctor or copy assignment op moves the res ownership to other auto_ptr
     * Sets old one to null (not great)
     * 
     * Can't be used in STL containers as they require "normal" copy semantics to be supported
     */


    /*
     * Shared Pointer
     * 
     * Reference counter, can have multple shared_ptrs to same resource. Will only delete it once no references to that object exist.
     * Can't break cyclic refernces. (2 objects that point to each other won't ever get deleted ( Garbage Collection can do this) )
     * CAN be used in STL containers.
     * 
     */

    void good()
    {
        class investment
        {};

        std::shared_ptr<investment> pInv(new investment);

        //Do stuff with pInv
    } // pInv is destroyed here via stack semantics, which invokes pInvs' dtor, which will delete and free up investment resource
}
