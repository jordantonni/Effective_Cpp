/*
 * Handle assignment to self in operator=
 * 
 * Not always easy to notice.
 * a[i] = a[j] could be assingment to self.
 * *px = *py could be assignment to self.
 * void func ( Base* bp, Derived* dp) could be assignment to self in body of function.
 * 
 * Best way is to use copy and swap idiom. Shown in item29 (exception safety)
 * 
 * Soltuion:
 * Check rhs address with this.
 * Careful ordering of statements (last implementation below) GOOD soltuion
 * copy and swap idiom BEST soltion
 * 
 * Note: Any function that operates on more than one object should ensure it behaves correctly if they are the same
 * 
 */


namespace item11
{
    class Bitmap
    { };

    class Widget
    {
        Bitmap* bp;
    public:

        // BAD -> if rhs is same object, we just deleted itself.
        // Exception unsafe
        //        Widget& operator=(const Widget& rhs)
        //        {
        //            delete bp;
        //            bp = new Bitmap(*rhs.bp);
        //            return *this;
        //        }

        // Exception unsafe -> If new bitmap throws, object is left in inconsistent state
        //        Widget& operator=(const Widget& rhs)
        //        {
        //            if (this == &rhs) return *this;
        //
        //            delete bp;
        //            bp = new Bitmap(*rhs.bp);
        //            return *this;
        //        }

        // GOOD -> Self assignment doesnt matter here
        // Exception safe also -> memeber variables keep their value until rhs assignment has succeeded
        Widget& operator=(const Widget& rhs)
        {
            Bitmap* pOriginal = bp;
            bp = new Bitmap(*rhs.bp);
            delete pOriginal;

            return *this;
        }
    };
}
