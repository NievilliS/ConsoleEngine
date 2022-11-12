#include <iostream>
#include <fstream>
#include <sstream>
#include "Pixel.hpp"

int main(int argc, char **argv)
{
    std::ifstream ifs("lol.txt");
    std::stringbuf sb;
    ifs >> &sb;
    pixelstr ps;
    Pixel::copy_string_to_pixel_string(ps, sb.str());

    Pixel::for_each(ps, [](auto i, auto c, auto t, auto o) -> void {
        static int cs = 0;
        if(c == ' ')
        {
            if(++cs > 7)
            {
                cs = 0;
            }
        }
        o = Pixel::int_to_color(cs);
    });
    std::cout << ps << std::endl;
}
