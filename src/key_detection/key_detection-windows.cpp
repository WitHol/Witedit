// This method of detecting keys only works for windows
#ifdef _WIN64

#include "key_detection.h"
#include "../header.h"

#include <windows.h>

std::vector<int> getKeys()
{
    std::vector<int> pressedKeys;

    for (int key = 0x01; key < 0xfe; ++key) 
    {
        if (GetAsyncKeyState(key) & 0x8000) 
        {
            pressedKeys.push_back(key);
        }
    }

    return pressedKeys;
}

std::vector<int> printableChars
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x', 'y', 'z'
};

std::vector<int> shiftedChars
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'W', 'X', 'Y', 'Z'
};

#endif