// A move-only RAII wrapper around the C file API (FILE*).
// The file is ALWAYS closed, even when an exception is thrown.
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <utility>

class File {
public:
    File(const char* path, const char* mode) : handle{std::fopen(path, mode)}, name{path}
    {
        if (!handle) throw std::runtime_error{std::string{"cannot open "} + path};
        std::cout << "  [open " << name << "]\n";
    }
    ~File()
    {
        if (handle) {
            std::fclose(handle);
            std::cout << "  [close " << name << "]\n";
        }
    }

    File(const File&) = delete;               // two owners of one handle = double close
    File& operator=(const File&) = delete;

    File(File&& other) noexcept : handle{std::exchange(other.handle, nullptr)}, name{other.name} {}
    File& operator=(File&& other) noexcept
    {
        if (this != &other) {
            if (handle) std::fclose(handle);
            handle = std::exchange(other.handle, nullptr);
            name = other.name;
        }
        return *this;
    }

    void write(const char* text) { std::fputs(text, handle); }

private:
    std::FILE* handle;
    const char* name;
};

void writeReport(bool fail)
{
    File f{"report.txt", "w"};
    f.write("line 1\n");
    if (fail) throw std::runtime_error{"something went wrong halfway"};
    f.write("line 2\n");
}   // f closes here: on success AND on failure

int main()
{
    writeReport(false);
    try {
        writeReport(true);
    } catch (const std::exception& e) {
        std::cout << "caught: " << e.what() << " (notice the file was still closed)\n";
    }
    File a{"a.txt", "w"};
    File b = std::move(a);   // ownership moves; only b will close the file
}
