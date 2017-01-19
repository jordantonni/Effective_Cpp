/*
 * Don't return a reference when you must return an actual Object
 * 
 * 
 * Never return a reference to a local (stack) variable.
 * Never return a pointer to a local (stack) variable.
 *  - The variable will be destroyed at end of scope and left with dangling pointer / reference.
 * 
 * Never return a reference to heap memory
 *  - No way to delete the object (using delete &referenceVar is a terrible idea)
 * 
 * Never return a reference or pointer to a local static object 
 *  - No thread sync and can cause issues if invoking the function > once in a statement
 *      - Both references would point to the exact same object!
 *  
 * TLDR: Returning an object or a refernce -> Return what is correct, don't worry about performance, let the compiler do that via return value optimization
 * 
 * 
 */
