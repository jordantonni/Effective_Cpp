/*
 * Use the same form in delete that you used in new
 * 
 * i.e.
 * Match new with delete
 * Match new [] with delete []
 * 
 * Why?
 *  new creates room on the heap for the sizeof some object
 *  new [] creates room on the heap for n objects + meta data at the start for how many objects there are
 *  
 *  New expression, what happens?:
 *  1 - New function is called, that allocates memory on the heap
 *  2 - Objects constructor(s) run, initializing that heap memory with values
 *  
 *  Delete expression, what happens?:
 *  1 - Objects destructor(s) run, which release resources
 *  2 - Function operator delete is called, which deallocates and returns the memory to the system
 *  
 *  Delete [] needs to know how many destructors to call of the n objects allocated in memory
 *  also needs to know the size of the memory to return
 *  It get's this information from the meta data created by new [n]
 *  
 *  Therefore ensure you use the same version of delete or delete [] with new or new []
 */

namespace item16
{
    void test()
    {
        int* single_dynamic_int = new int(5);
        delete single_dynamic_int;

        int* multiple_dynamic_ints = new int[1024];
        delete[] multiple_dynamic_ints;
    }
}
