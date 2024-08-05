#include "header.h"

/*
This file contains functions, that aren't realted to the program specifficaly,
but are needed at some point
*/

inline bool contains(const std::vector<int>& vec, int element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

enum class DirEnum
{
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
};