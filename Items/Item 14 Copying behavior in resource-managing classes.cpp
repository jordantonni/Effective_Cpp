/*
 * Think carefully about the copying behavior in resource-managing classes
 * 
 * Smart pointers such as auto_ptr and shared_ptr are good for providing a resource management class for a heap based resource.
 *  
 * But this is not the only type of resource. Others such as DB connections, sockets, mutexs etc don't work well in this context.
 * So need to create your own resource managing class.
 * 
 * What should happene with RAII object is copied (Question every RAII class MUST address)
 * 1) Disalow copying -> delete copy ctor and assingment op
 * 2) Reference count copy -> use shared_ptr in your resource management class
 *    Provide a custom deleter for the specific object type to the shared_ptr
 * 3) Copy underlying resource - Deep Copy (E.g. like the string class does)
 * 4) Transfer Ownership - e.g. like auto_ptr (rarely used)
 * 
 * Remember:
 * The copying behavior of the RESOURCE should determine the copying behavior of the resource-management class.
 * Most typical things are either resource counting (using shared ptr with custom deleter) and disallowing copying
 */

#include <mutex>

namespace item14
{
    // Example of a class that would resource manage a mutex, called Lock

    void lock(std::mutex* m);
    void unlock(std::mutex* m);

    class Lock
    {
        std::mutex* m;

    public:
        // Locks the mutex on acquisition
        explicit Lock(std::mutex* const mut)
            : m { mut }
        {
            lock(m);
        }

        // Unlocks the mutex one deletion / out of scope
        ~Lock()
        {
            unlock(m);
        }
    };


    /*
     * Custom deleter example
     * 
     * We close DBConn using the static close methid in its class.
     * The resource manager class has a shared ptr to a DBConn and we give the close method to its deleter.
     * 
     * It then calls close once DB_Resource_Manager goes out of scope, instead of calling delete etc.
     * 
     */

    class DBConn
    {
    public:
        static void close(DBConn* db)
        { }
    };

    class DB_Resource_Manager
    {
        std::shared_ptr<DBConn> dbc;
    public:
        DB_Resource_Manager(DBConn* const db)
            : dbc{ db, DBConn::close }
        {}
    };
}
