// std::filesystem: work with paths and folders portably.
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    const fs::path dir = fs::current_path() / "demo_folder";
    fs::create_directories(dir / "notes");   // makes all missing folders

    std::ofstream{dir / "hello.txt"} << "Hello, filesystem!\n";
    std::ofstream{dir / "notes" / "todo.md"} << "- learn C++\n- build things\n";

    std::cout << "Working in: " << dir << "\n\n";
    for (const auto& entry : fs::recursive_directory_iterator{dir}) {
        const auto& p = entry.path();
        std::cout << (entry.is_directory() ? "[dir]  " : "[file] ") << fs::relative(p, dir).string();
        if (entry.is_regular_file()) std::cout << "  (" << entry.file_size() << " bytes, extension " << p.extension() << ")";
        std::cout << '\n';
    }

    std::cout << "\nhello.txt exists? " << std::boolalpha << fs::exists(dir / "hello.txt") << '\n';
    fs::remove_all(dir);   // clean up the demo
    std::cout << "cleaned up, exists now? " << fs::exists(dir) << '\n';
}
