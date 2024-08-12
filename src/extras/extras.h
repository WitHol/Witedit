/*
This file contains functions, that aren't realted to the program specifficaly,
but are needed at some point
*/

#ifndef EXTRAS
#define EXTRAS

#include "../header.h"


// This function checks, wherher an elemnt is a member of a vector/array
bool contains(const std::vector<int>& vec, int element);

bool contains(int array[], int arrayLen, int element);

int shiftedChar(int char_);

// An enum for directions
enum class DirEnum
{
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
};

#endif