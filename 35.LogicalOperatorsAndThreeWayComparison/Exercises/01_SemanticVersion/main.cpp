// ⭐⭐ Exercise 01: SemanticVersion
// struct Version { int major, minor, patch; }
// 1. Add defaulted == and <=> (members are compared in declaration order).
// 2. Add operator<< printing "1.10.2".
// 3. Sort this list with std::sort and print it:
//      {1,10,0} {1,2,3} {2,0,0} {1,2,10} {0,9,9}
//    Expected: 0.9.9 1.2.3 1.2.10 1.10.0 2.0.0
//    (Notice: "1.10.0" > "1.2.10" as versions, but NOT as strings!)
// 4. Print whether Version{1,2,3} >= Version{1,2,3}.
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // TODO
}
