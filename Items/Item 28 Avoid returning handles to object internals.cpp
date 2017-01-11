/*
 * Avoid returning handles to object internals
 * 
 * 
 * References, Pointers, Iterators -> Handles:
 *  - Ways to get at the object internals
 *  
 * 
 * Rules
 * 1) A data member is only as a encapsulated as the most accessible function returning a reference to it
 * 2) If a const member function returns a reference to a object stored outside the class itself, e.g. pointer to it, the caller can modify it
 * 
 * Even in a const function, returning a reference to a data member allows it to be changed. 
 * Never have a member function return a pointer to a less accessible member function
 * If returning a reference to a data memeber, return a const reference
 * 
 * Dangling handles:
 *  - Occurs when you return a refence to something that no longer exists.
 * 
 * SUMMARY:
 *  - Don't return handles (references, pointers, iterators) to object internals
 * 
 */


