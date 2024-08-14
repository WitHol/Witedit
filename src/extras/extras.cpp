#include "extras.h"


bool contains(const std::vector<int>& vec, int element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

bool contains(const std::vector<wchar_t>& vec, wchar_t element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

bool contains(int array[], int arrayLen, int element)
{
    for(int i = 0; i < arrayLen; ++i)
    {
        if(array[i] == element) return true;
    }

    return false;
}

bool contains(wchar_t array[], int arrayLen, wchar_t element)
{
    for(int i = 0; i < arrayLen; ++i)
    {
        if(array[i] == element) return true;
    }

    return false;
}


int shiftedChar(int char_)
{
    const int shiftedChars[] = {
        'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z',
        '1', '!', '2', '@', '3', '#', '4', '$', '5', '%', '6', '^', '7', '&', '8', '*', '9', '(', '0', ')',
        '-', '_', '=', '+', '[', '{', ']', '}', '\\', '|', ';', ':', '\'', '"', ',', '<', '.', '>', '/', '?', '`', '~',
    0};

    for(const int *i = shiftedChars; *i != 0; i += 2)
    {
        if(*i == (int)char_) return *(i + 1);
    }

    return char_;
}

char asciiChars[] = {
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
};