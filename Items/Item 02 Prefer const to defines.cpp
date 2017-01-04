/*
 * Prefer consts, enums and inline to #defines.
 * 
 * Use consts and enums instead of simple defines. Enum hack can be used, though not needed anymore unless in Template meta prog.
 * 
 * Replace function macros with inline functions.
 *  Inline replaces the function invocations/calls with the literal function body text code.
 */

#include <string>

namespace item02
{
    //Ensure both data and pointer are const
    const char * const name = "Jordan";
    //Prefer string objects to char*
    const std::string myName("Jordan");


    class GamePlayer
    {
        // static members in classes are only DECLARATIONS, not definiitons. So typically you need to define the variable outside the class also
        // static const integtral types are the only exception to this rule, they are defined as below OK.
        static const int numTurns = 5; 
        // This string must be defined outside the class as below
        static const std::string game_name;
        // Must also be defined outside the class as it's not a const static
        static int count;
    };

    // This would be in the Implementation file, not the header!
    // Why? Because it would be initialized everytime it was #included from it's header file!
    const std::string GamePlayer::game_name("Monopoly");
    int GamePlayer::count = 7;


    // Old compilers incorrectly dont allow in the class initialization of static const int types
    // If we need to use their value at class compile time (where the class is usually defined in the header) we used
    // The Enum Hack
    class enum_hack
    {
        enum
        {
            numTurns = 5
        };
        int scores[numTurns]; // Uses the enum value at compile time. Doesnt set aside storage either, so similar to define. 
    };
}
