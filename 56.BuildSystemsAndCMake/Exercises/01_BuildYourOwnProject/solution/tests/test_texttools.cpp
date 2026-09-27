#include <texttools/texttools.h>

#include <iostream>

int main()
{
    int failures = 0;
    auto check = [&](bool ok, const char* what) {
        if (!ok) {
            ++failures;
            std::cerr << "FAIL: " << what << '\n';
        }
    };
    check(texttools::toUpper("abc") == "ABC", "toUpper");
    check(texttools::split("a,b", ',').size() == 2, "split count");
    check(texttools::join({"a", "b"}, "-") == "a-b", "join");
    std::cout << (failures ? "FAILED\n" : "all tests passed\n");
    return failures;
}
