#include <iostream>
#include <iomanip>

unsigned int pack(unsigned int r, unsigned int g, unsigned int b)
{
    return ((r & 0xFFu) << 16) | ((g & 0xFFu) << 8) | (b & 0xFFu);
}

unsigned int red(unsigned int c)   { return (c >> 16) & 0xFFu; }
unsigned int green(unsigned int c) { return (c >> 8) & 0xFFu; }
unsigned int blue(unsigned int c)  { return c & 0xFFu; }

void unpack(unsigned int color)
{
    std::cout << std::dec << "R=" << red(color) << " G=" << green(color) << " B=" << blue(color) << '\n';
}

void printHex(const char* label, unsigned int color)
{
    std::cout << label << "0x" << std::hex << std::uppercase << std::setw(6) << std::setfill('0')
              << color << std::dec << '\n';
}

int main()
{
    const unsigned int orange = 0xFF8800;
    const unsigned int blueC = 0x0044FF;
    unpack(orange);
    unpack(blueC);

    unsigned int mixed = pack((red(orange) + red(blueC)) / 2,
                              (green(orange) + green(blueC)) / 2,
                              (blue(orange) + blue(blueC)) / 2);
    printHex("Mixed : ", mixed);
    unpack(mixed);

    unsigned int darker = pack(red(orange) >> 1, green(orange) >> 1, blue(orange) >> 1);
    printHex("Darker orange: ", darker);
}
