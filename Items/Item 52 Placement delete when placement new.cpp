/* 
 * Placement new and placement delete
 * 
 * Widget* pw = new Widget(val);
 * 
 * Calls new + Widget ctor
 * If ctors throws, pointer to mem allocated with new never given to pw, so we can't delete it.
 * -> operator new must handle this!
 * 
 * Placement new: 
 *  - If operator new takes more parameters than default size_t, it's called a placement new
 *  - operator new(size_t size, void* pMemory)
 *      - Is an inbuilt placement new where pMemory determines where to place the allocated memory on the heap
 * 
 * Problem:
 *  - If we declare our own placement new, with more params, we dont have a matching delete with the same number and type of params
 *      -> This is needed for new to call if the ctor of the new'd object throws
 *  
 * Solution:
 *  - For any placement new, write the same signiture placement delete
 *
 *
 * SUMMARY
 *  - Write corresponding placement delete for placement new
 *  - Placement new and deletes will hide normal versions of new and delete, bring them back into use via using statements
 */

namespace item52
{ }
