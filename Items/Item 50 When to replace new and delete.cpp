/* Understand when it makes sense to replace new and delete
 * 
 * - Detect usage errors via tallying news with delete
 * - Collect statistics of how the memory is being allocated
 * - Increase speed based on tuning for specific sizes etc
 * - Reduce space overhead from blocks allocated
 * - Enforce allignment for faster access on certain architectures
 * - Cluster objects together to reduce page faults
 * 
 * Allignment: Some data types, e.g. double, need to be 8-byte alligned for optimal performance
 *
 */

#include <new>
#include <math.h>

namespace item50
{
    /*
     * Naive new
     */
    static const int signiture = 0xDEADBEEF; // Used to mark the beginning and end of alloacted memory block to test for under and over writes!

    typedef unsigned char Byte;

    void* operator new(std::size_t size) throw(std::bad_alloc)
    {
        using namespace std;

        size_t real_size = size + (2 * sizeof(int)); // Space for signiture

        void* pMem = malloc(real_size); // Get memory

        *(static_cast<int*>(pMem)) = signiture; // Write signiture to start of block

        *(reinterpret_cast<int*>(static_cast<Byte*>(pMem) + (real_size - sizeof(int)))) = signiture; // Write signiture to end of block

        return static_cast<Byte*>(pMem) + sizeof(int);
    }
}
