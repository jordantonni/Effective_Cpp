/*
 * Strive for exception safe code
 * 
 * Requirements for exception safety
 *  1) Leak no resources
 *  2) Don't allow data structures to become corrupted
 *
 * Three exception safety guarantees:
 * 1) Basic Guarantee - No resource leaks + Data in (some) consistent valid state 
 * 2) Strong Guarantee - No resource leaks + Data in same state as it was before call
 * 3) No Throw Guarantee - Always succeeds. All operations on built-in types never throw.
 * 
 * Copy and Swap:
 * - Copy the object to a temp
 * - Modify the copy
 * - swap the orignal with the temp, using your no throw swap implementation
 * 
 * - Typically implemented via Pimpl
 * - Storing all object data in the pimpl then you can just swap the pointers at the end
 * 
 * SUMMARY:
 *  - Exception safe functions leak no resources and keep the data members in a valid state. Even if exceptions are thrown
 *  - Can use copy and swap to implement Strong Safety Guarantee, but the copying can be costly
 *  - Function is only as exception safe as the weakest function it calls
 */
#include <mutex>
#include <memory>
#include <istream>
using namespace std;

namespace item29
{
    struct Image
    {
        int val;
        string src;

        explicit Image(const istream& src)
        {}

        explicit Image(const string& src = "def", int v = 0)
            : val{ v }
            , src{ src }
        {}
    };

    class DesktopBackground
    {
        mutex mutex;
        int imageChanges;

        // Bad
        Image* img;
        // Good
        shared_ptr<Image> imgPtr;

    public:
        /*
         * Not exception safe
         * 
         * Leaks Resources -> If new Image throws, mutex.unlock() is never called
         * Corrupts Data   -> If new Image throws, img points to a deleted memory location
         */
        void change_background_unsafe(istream& img_src)
        {
            mutex.lock();

            delete img;
            ++imageChanges;
            img = new Image(img_src);

            mutex.unlock();
        }

        /*
         * Basic Safety Guarantee
         * 
         * Lockguard offers RAII on the mutex -> No resource leak on the mutex even if new Image throws
         * imgPtr stored as a shared_ptr gives RAII -> Reset ensures the pointer only deletes and points to the new img_src if it succeeds
         * 
         * Not Strong Guarantee- Why?
         * img_src is passed as an istream, if New Image throws the read on img_src may have moved forward -> state of object has changed from before call
         */
        void change_background_basic(istream& img_src)
        {
            lock_guard<std::mutex> lock(mutex);

            imgPtr.reset(new Image(img_src));
            ++imageChanges;
        }

        /*
         * Strong Safety Guarantee
         * 
         * Same as above but passing by a string means instead of istream fixes above issue
         */
        void change_background_strong(const string& img_src)
        {
            lock_guard<std::mutex> lock(mutex);

            imgPtr.reset(new Image(img_src));
            ++imageChanges;
        }
    };

    /*
     * Copy and Swap version
     */

    struct PMImpl
    {
        shared_ptr<Image> bgIMage;
        int imageChanges;

        PMImpl()
            : bgIMage { new Image }
            , imageChanges { 0 }
        { }

        void swap(shared_ptr<PMImpl> p)
        {
            using std::swap;
            swap(imageChanges, p->imageChanges);
            swap(bgIMage, p->bgIMage);
        }
    };

    void swap(shared_ptr<PMImpl> P1, shared_ptr<PMImpl> P2)
    {
        P1->swap(P2);
    }

    class DesktopBg
    {
        mutex mutex;

    public:
        shared_ptr<PMImpl> pimpl;

        DesktopBg()
            : pimpl { new PMImpl }
        { }

        void change_background_copy_and_swap(const string& img_src)
        {
            using std::swap; // Find and fall back to std::swap if we didn't define our own

            lock_guard<std::mutex> lock(mutex);
            shared_ptr<PMImpl> copy(new PMImpl(*pimpl));

            copy->bgIMage.reset(new Image(img_src));
            ++copy->imageChanges;

            swap(pimpl, copy);
        }
    };

    void test()
    {
        DesktopBg one;
        one.change_background_copy_and_swap("two");
    }
}
