// ⭐⭐⭐ Exercise 03: ConnectionPool
// Databases limit how many connections you may open, so apps keep a POOL and reuse them.
// 1. class Pool { explicit Pool(int size); Lease acquire(); int available() const; }
//    acquire() throws std::runtime_error if none are free.
// 2. class Lease: a MOVE-ONLY RAII handle to one connection id.
//      - its destructor RETURNS the connection to the pool automatically
//      - moving a Lease transfers the responsibility (the moved-from one returns nothing)
//      - int id() const
// 3. Show: acquire 2 of 3, print available (1); let one Lease go out of scope (2);
//    move a Lease into a function that uses it and ends (connection returned);
//    acquire 4 in a row → the 4th throws, and after the exception all are back (3).
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
    // TODO
}
