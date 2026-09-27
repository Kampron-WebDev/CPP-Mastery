// Project 06: MiniGrep. See README.md. Run from a terminal: .\rooster.exe pattern file.txt
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [options] <pattern> <file>...\n";
        return 2;
    }
    std::cout << "TODO: search for '" << argv[argc - 2] << "'\n";
}
