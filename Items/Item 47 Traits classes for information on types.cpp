/*
 * Use Traits classes for information about Types
 * 
 * Traits allow you to get information on a type during compilation.
 * Can't just include traits information inside classes as they need to also work with primitive types.
 * 
 * - Tag struct: Empty class that declares a name / tag to identify some behavior or information about a class/type you want to make availble.
 * 
 * - Traits class: Templated struct that has typedefs templated parameters nested tag struct.
 *                 Basically makes the behavior supported, given by the nested tag struct in the class, availble
 *                 
 * - Partial template specialization of traits class: Can typedef built in types, such as pointers, setting the typedef manually
 *                                                    Needed because a built in type cant have a nested tag struct!
 * 
 * Can use typeid( typename widget_traits<Widget>::widget_tag )
 *  - To get the information on the class and then do stuff with it depending on that. Not a good way though
 *      - If statements are run time, we want compile time decisions on the information we get here
 *  
 * Better way?
 *  - Function overloading is a compile time decision. 
 *  - Replace if statements with different functions taking the different Tag structs we defined as a parameter
 *      - Invoke the function with typename widget_traits<Widget>::widget_tag as an argument to select the correct one at compile time!
 * 
 * SUMMARY:
 *  - Traits classes make information about types ( declared as tag structs ) availble at compile time.
 *      - Traits classes do this via taking the type as a template parameter and typedefing its nested tag struct
 *  
 *  - Make decisions on the traits the class has using function overloading with arguments on that tag struct type
 *      - this is compile time, if else are runtime, which is not good!
 */


namespace item47
{
    
}
