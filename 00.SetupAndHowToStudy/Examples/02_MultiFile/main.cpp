// Two .cpp files in one folder. The build task compiles *.cpp,
// so both are compiled and joined (linked) into one program.
#include "greet.h"

int main()
{
    greet("Ada");
    greet("Linus");
}
