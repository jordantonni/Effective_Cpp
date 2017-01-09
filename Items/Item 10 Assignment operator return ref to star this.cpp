/*
 * Assignment operators should return a reference to *this
 * 
 * Assignment can be chained:
 * a = b = c = 15
 * 
 * -> ( a = ( b = ( c = 15) ) ; // Is how this really gets executed. 
 * 
 * Each assignment operation returns the value assignment via reference to its left hand argument (*this). So it can be used as the input to another assingment.
 *
 * Doing this with your own classes makes it consistent with the convention of built-in types. A good thing.
 */


namespace item10
{
    class Widget
    {
    public:
        // ANY assignment operator should return reference to *this.

        Widget& operator=(const Widget& rhs)
        {
            // ...
            return *this;
        }

        Widget& operator=(int rhs)
        {
            // ...
            return *this;
        }

        Widget& operator+=(const Widget& rhs)
        {
            // ...
            return *this;
        }
    };
}
