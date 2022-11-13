#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Pixel.hpp"

int main(int argc, char **argv)
{
    std::ifstream ifs("lol.txt");
    std::stringbuf sb;
    ifs >> &sb;
    pixelstr ps;
    Pixel::copy_string_to_pixel_string(ps, sb.str());

    auto start = std::chrono::steady_clock::now();
    auto ela = start-start;

    int cs = 0;

    Pixel::for_each(ps, [](auto i, auto c, auto t, auto o, auto f) -> void {
        o = Pixel::YELLOW;
        static int cs = 0;
        if(c == ' ')
        {
            if(++cs > 1)
            {
                cs = 0;
            }
        }
        f = cs ? Pixel::BOLD : Pixel::NORMAL;
    });

    ela = std::chrono::steady_clock::now()-start;

    //for(char c : Pixel::to_string(ps))
    //{
    //    if(c == '\033') std::cout << '*';
    //    std::cout << c;
    //}
    std::cout << ps << std::endl;

    std::cout << COLOR_RESET << "\nTook " << COLOR_FONT_UNDERLINED << std::chrono::duration_cast<std::chrono::milliseconds>(ela).count() << "ms" << COLOR_RESET << std::endl;
}
