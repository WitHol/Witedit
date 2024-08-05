/*
This is the main header file included in every source file
*/

#ifndef HEADER
#define HEADER

// Including all the necessary libraries
#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <iostream> // Only here for debugging
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// Inner header files
#include "editor_window/editor_window.h"
#include "key_detection/key_definitions.h"
#include "key_detection/key_detection.h"
#include "extras.cpp"

// A variavle for stopping the program afer ctrl-q
extern bool end;

#endif