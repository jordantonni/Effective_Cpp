/*
 * Prefer non-member non-friend functions over member functions
 * 
 * Encapsulation -> Memebers are hidden from view
 *  - Changes only affect something when outside world can see it has changed
 *  - Therefore, more encapsulation means more freedom to change
 *  
 * The more functions that can see data, the less encapsulated something is.
 * 
 * A non-memeber non-friend function has less access to those private memebers
 *  - So if you can implement something using such a function -> results in more encapsulation!
 *  
 * Convenience Functions:
 *  - Functions that have no more access to a class than any other normal non-memeber non-friend function
 *  - Carry out stuff that helps, e.g. the clearEverything function below!
 * 
 * Implement convenience functions as non-memeber non-friend functions
 * Put them in their own namespace in another header
 * Why?
 *  - Same reason the Standard Library is split into multiple headers under one std:: namespace
 *      - No compilation dependences on all the different functions, can group what you need in logicaly similar headers, all under same namespace
 *      - Note: Can't do this with a class method, as they are all compiled as part of it
 *      - Allows for easy extention by making your own header functions under same namespace
 *          - Open for extention, closed for modification!
 *  
 *  
 *  NOTE: This preference is ONLY between memeber functions and non-member NON-FRIEND
 *        Not between member and non-member only
 */

namespace item23
{
    namespace WebBrowserStuff
    {
        //WebBrowserCore.h

        class WebBrowser
        {
        public:
            void clearCache()
            {}

            void clearHistory()
            {}

            // void clearEverything(); -Don't have this as a member, its a convienence function.
        };
    }

    //WebBrowserHistory.h
    namespace WebBrowserStuff
    {
        void clearEverything(WebBrowser& wb)
        {
            wb.clearCache();
            wb.clearHistory();
        }
    }
}
