#pragma once

#include <iostream>
#include "smartptr.hpp"



class ConsoleEngine
{
protected:
    smartptr<char> m_data;
    int m_cursorx;
    int m_cursory;
    int m_startx;
    int m_starty;
}
