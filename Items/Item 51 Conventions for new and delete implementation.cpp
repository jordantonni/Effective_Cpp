/* 
 * Adhere to convetion when writing new and delete
 *
 *
 * New should:
 *  - Return the correct return value
 *  - Call new-handle function when can't allocate memory
 *  - Cope with requests to no memory
 *  
 *  Ensure you don't hide default new when overriding this for classes. i.e. using statements
 *  
 * How new works:
 *  - Test if size requested is 0, if it is set size to 1
 *  - Infinite loop to try and malloc memory needed
 *      - If successful return pointer to memory
 *      - If not successful:
 *          - Get new_handler
 *          - Test if it's null
 *              - If it is, throw bad alloc
 *              - If not, call it
 *              
 *              
 * Class override operator new:
 *  - Derived types inherit base operator new
 *  - Typically, if you are overriding this function, you are tuning it to the size of the class
 *      - size(base) will be smaller than size(derived)
 *          -> Test for this first, if false, invoke return ::operator new(size)
 *          
 * Delete:
 *  - Check if the pointer is 0 / null
 *      - Return
 *  - Deallocate it
 *  
 * Delete for classes:
 *  - Need to take an overloaded delete that takes a size as well as a pointer
 *  - Checks the sizeof(base) != size
 *      - If so, the ::operator new was called, so call ::delete
 *  
 *
 * SUMMARY
 *  - Operator new should infinite loop trying to get memory
 *  - Call new-handler if can't get it
 *  - Zero memory should be handled, such as just asking for 1 byte
 *  - delete should return if null pointer
 *  
 *  - Class (inheritance) specific versions should handle if the size requested DNE sizeof(their type)
 *      - In new, if not the same, call the ::operator new
 *      - In delete, take size as a 2nd param, if not the same call ::delete
 */

namespace item51
{ }
