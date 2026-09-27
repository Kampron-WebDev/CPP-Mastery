#include <iostream>

#include "widget.h"

int main()
{
    Widget ok{"OK button"};
    ok.click();
    ok.click();
    std::cout << ok.describe() << '\n';
}
