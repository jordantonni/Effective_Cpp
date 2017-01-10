/*
 * Treat class design as type design
 * 
 * How should the new type be created and destroyed
 *  - ctor / dtor / operator new / operator delete
 * 
 * How should initialization differ from assignment
 *  - ctor vs assignment opererators
 * 
 * How does pass by value work for your type
 *  - Copy ctor defines how this works
 * 
 * What values make your Type legal and valid
 *  - Valid values for class memebers -> class invariant to maintain
 *  - Class Invariant -> Error checking needed in ctor / setters / assignment operators / etc
 *  - Affects exceptions the class will throw
 *  
 * Will the type be used in an Inhertiance hierarchy / graph
 *  - If it inherits from another class -> constrained by their virtual interface
 *  - If it will be inherited from -> Think carefully about what to make virtual, especially make dtor virtual
 *  
 * Type conversions
 *  - Provide explicit conversions only? -> method that returns Type T1 as T2, e.g. get()
 *  - Provide implicit conversions also? -> operator T2() const, non explicit ctor(T2)
 * 
 * What functions should be member methods or friend functions
 *  - Conversion operators > 2 args as friend
 * 
 * What Standard functions to disallow
 *  - default ctor, copy ctor, dtor, copy assingment op -> Declare as private to delete
 * 
 * Who should have access to the memebers of the Type
 *  - What should be public, private
 *  - Who should be a friend
 *  
 * What is the Undeclared Interface of your Type
 *  - Exception guarantees
 *  - Performance
 *  
 * How General is the Type
 *  - Are you defining a family of types, of so -> Make it a template
 * 
 * Do you need a new Type
 *  - If only adding new functionality to some class -> can it be done via non-member functions or templates
 * 
 * 
 */