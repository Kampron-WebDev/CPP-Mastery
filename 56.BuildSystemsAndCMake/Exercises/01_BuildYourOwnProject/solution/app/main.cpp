#include <texttools/texttools.h>

#include <iostream>

int main()
{
    const auto words = texttools::split("modern,cpp,is,fun", ',');
    std::cout << texttools::toUpper(texttools::join(words, " ")) << '\n';
}
