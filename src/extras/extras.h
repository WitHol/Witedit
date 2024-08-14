/*
This file contains functions, that aren't realted to the program specifficaly,
but are needed at some point
*/

#ifndef EXTRAS
#define EXTRAS

#include "../header.h"


// This function checks, wherher an elemnt is a member of a vector/array
bool contains(const std::vector<int>& vec, int element);

bool contains(const std::vector<wchar_t>& vec, wchar_t element);

bool contains(int array[], int arrayLen, int element);

bool contains(wchar_t array[], int arrayLen, wchar_t element);


int shiftedChar(int char_);

// An enum for directions
enum class DirEnum
{
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
};

// This array contains all printable ASCII characters
extern char asciiChars[];

#endif