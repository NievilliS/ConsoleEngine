#pragma once

#define ANSI_DEFAULT_STREAM std::cout
#define ANSI_DEFAULT_FLUSH std::flush
#include "ANSICONSTANTS"

#include <iostream>
#include <cstring>

typedef __UINT16_TYPE__ Pixel_t;
typedef std::basic_string<Pixel_t> pixelstr;

Pixel_t operator "" us(unsigned long long val)
{
    return (Pixel_t) val;
}

__UINT8_TYPE__ operator "" uc(unsigned long long val)
{
    return (__UINT8_TYPE__) val;
}

namespace Pixel
{
    enum ColorType : __UINT8_TYPE__
    {
        TEXT,
        BACKGROUND
    };

    enum Color : __UINT8_TYPE__
    {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        DEFAULT
    };

    inline static const Color int_to_color(const __UINT8_TYPE__ val)
    {
        switch(val)
        {
            case 0u:
                return BLACK;
            case 1u:
                return RED;
            case 2u:
                return GREEN;
            case 3u:
                return YELLOW;
            case 4u:
                return BLUE;
            case 5u:
                return MAGENTA;
            case 6u:
                return CYAN;
            case 7u:
                return WHITE;
        }
        return DEFAULT;
    }
    
    inline static Pixel_t create_pixel(const unsigned char character, const ColorType color_type, const Color color)
    {
        return (character > 0uc) ? (character | (color_type << 8) | (color << 9)) : 0us;
    }

    inline static Color get_pixel_color(const Pixel_t pixel)
    {
        return int_to_color(((__UINT8_TYPE__)(pixel >> 9)) & 0x0Fuc);
    }

    inline static void set_pixel_color(Pixel_t &pixel, const Color color)
    {
        pixel = (pixel & 0xE1FFus) | ((color << 9) & 0x1E00us);
    }

    inline static ColorType get_pixel_color_type(const Pixel_t pixel)
    {
        return ((((__UINT8_TYPE__)(pixel >> 8)) & 0x01uc) > 0x00uc) ? BACKGROUND : TEXT;
    }

    inline static void set_pixel_color_type(Pixel_t &pixel, const ColorType color_type)
    {
        pixel = (pixel & 0xFEFFus) | ((color_type << 8) & 0x0100us);
    }

    inline static unsigned char get_pixel_char(const Pixel_t pixel)
    {
        return (unsigned char)(pixel & 0x00FFus);
    }

    inline static void set_pixel_char(Pixel_t &pixel, unsigned char character)
    {
        pixel = (pixel & 0xFF00us) | (character & 0x00FFus);
    }

    std::string to_string(const Pixel_t &pixel)
    {
        std::string ret = "";
        static Color old_color = DEFAULT;
        static ColorType old_type = TEXT;
        Color now_color = get_pixel_color(pixel);

        if(old_color != now_color && get_pixel_color_type(pixel) == TEXT)
        {
            switch(now_color)
            {
            case BLACK:
                ret = COLORT_BLACK; break;
            case RED:
                ret = COLORT_RED; break;
                
            case GREEN:
                ret = COLORT_GREEN; break;
            case YELLOW:
                ret = COLORT_YELLOW; break;
            case BLUE:
                ret = COLORT_BLUE; break;
            case MAGENTA:
                ret = COLORT_MAGENTA; break;
            case CYAN:
                ret = COLORT_CYAN; break;
            case WHITE:
                ret = COLORT_WHITE; break;
            case DEFAULT:
                ret = COLORT_DEFAULT; break;
            }
        }
        else
        {
            switch(now_color)
            {
            case BLACK:
                ret = COLORB_BLACK; break;
            case RED:
                ret = COLORB_RED; break;
            case GREEN:
                ret = COLORB_GREEN; break;
            case YELLOW:
                ret = COLORB_YELLOW; break;
            case BLUE:
                ret = COLORB_BLUE; break;
            case MAGENTA:
                ret = COLORB_MAGENTA; break;
            case CYAN:
                ret = COLORB_CYAN; break;
            case WHITE:
                ret = COLORB_WHITE; break;
            case DEFAULT:
                ret = COLORB_DEFAULT; break;
            }
        }
        
        ret += get_pixel_char(pixel);
        return ret;
    }

    inline static const size_t get_pixel_string_length(const Pixel_t *pixel)
    {
        size_t i = 0;
        for(; pixel[i] & 0x00FFus > 0u; i++);
        return i;
    }

    std::string to_string(const Pixel_t *pixels)
    {
        std::string ret = "";
        const size_t max = get_pixel_string_length(pixels);
        for(size_t i = 0; (pixels[i] & 0x00FFus) > 0u; i++)
        {
            ret += to_string(pixels[i]);
        }
        return ret;
    }

    std::string to_string(const pixelstr ps)
    {
        return to_string(ps.c_str());
    }

    inline static void copy_string_to_pixel_string(const size_t max_size, Pixel_t *pixel_dest, const char *cstr_source,
        void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color)
    ) {
        for(size_t i = 0; i < max_size; i++)
        {
            char character = (char) cstr_source[i];
            ColorType color_type = TEXT;
            Color color = DEFAULT;
            lambda_function(i, character, color_type, color);
            pixel_dest[i] = Pixel::create_pixel(character, color_type, color);
        }
    }

    inline static void copy_string_to_pixel_string(const size_t max_size, Pixel_t *pixel_dest, const char *cstr_source)
    {
        for(size_t i = 0; i < max_size; i++)
        {
            pixel_dest[i] = Pixel::create_pixel(cstr_source[i], TEXT, DEFAULT);
        }
    }

    inline static void copy_string_to_pixel_string(Pixel_t *pixel_dest, const std::string str_source,
        void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color)
    ) {
        size_t i = 0;
        for(char c : str_source)
        {
            char character = c;
            ColorType color_type = TEXT;
            Color color = DEFAULT;
            lambda_function(i, character, color_type, color);
            pixel_dest[i++] = Pixel::create_pixel(character, color_type, color);
        }
    }

    inline static void copy_string_to_pixel_string(Pixel_t *pixel_dest, const std::string str_source)
    {
        size_t i = 0;
        for(char c : str_source)
        {
            pixel_dest[i++] = Pixel::create_pixel(c, TEXT, DEFAULT);
        }
    }

    inline static void copy_string_to_pixel_string(const size_t max_size, pixelstr &pixel_dest, const char *cstr_source,
        void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color)
    ) {
        pixel_dest.clear();
        for(size_t i = 0; i < max_size; i++)
        {
            char character = (char) cstr_source[i];
            ColorType color_type = TEXT;
            Color color = DEFAULT;
            lambda_function(i, character, color_type, color);
            pixel_dest += Pixel::create_pixel(character, color_type, color);
        }
    }

    inline static void copy_string_to_pixel_string(const size_t max_size, pixelstr &pixel_dest, const char *cstr_source)
    {
        pixel_dest.clear();
        for(size_t i = 0; i < max_size; i++)
        {
            pixel_dest += Pixel::create_pixel((char) cstr_source[i], TEXT, DEFAULT);
        }
    }

    inline static void copy_string_to_pixel_string(pixelstr &pixel_dest, const std::string str_source,
        void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color)
    ) {
        pixel_dest.clear();
        size_t i = 0;
        for(char c : str_source)
        {
            char character = c;
            ColorType color_type = TEXT;
            Color color = DEFAULT;
            lambda_function(i++, character, color_type, color);
            pixel_dest += Pixel::create_pixel(character, color_type, color);
        }
    }

    inline static void copy_string_to_pixel_string(pixelstr &pixel_dest, const std::string str_source)
    {
        pixel_dest.clear();
        for(char c : str_source)
        {
            pixel_dest += Pixel::create_pixel(c, TEXT, DEFAULT);
        }
    }

    inline static void for_each(pixelstr &pixel_dest, void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color))
    {
        size_t i = 0;
        for(Pixel_t &p : pixel_dest)
        {
            char character = get_pixel_char(p);
            ColorType color_type = get_pixel_color_type(p);
            Color color = get_pixel_color(p);
            lambda_function(i++, character, color_type, color);
            p = create_pixel(character, color_type, color);
        }
    }

    inline static void for_each(size_t size, Pixel_t *pixel_dest, void (*lambda_function)(const size_t index, char &character, ColorType &color_type, Color &color))
    {
        for(size_t i = 0; i < size; i++)
        {
            char character = get_pixel_char(pixel_dest[i]);
            ColorType color_type = get_pixel_color_type(pixel_dest[i]);
            Color color = get_pixel_color(pixel_dest[i]);
            lambda_function(i, character, color_type, color);
            pixel_dest[i] = create_pixel(character, color_type, color);
        }
    }
};

std::ostream &operator<<(std::ostream &o, pixelstr ps)
{
    return o << Pixel::to_string(ps);
}

pixelstr operator "" ps(const char *c, size_t size)
{
    pixelstr ps;
    for(size_t i = 0ULL; i < size; i++)
        ps += Pixel::create_pixel(c[i], Pixel::TEXT, Pixel::DEFAULT);
    return ps;
}
