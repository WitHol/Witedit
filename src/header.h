/*
This is the main header file included in every source file
*/

#ifndef HEADER
#define HEADER

// This is apparently needed for ncurses to diplay non-ASCII characters
#define _XOPEN_SOURCE_EXTENDED

// Including all the necessary libraries
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>

// This is for stopping the program
extern bool end;

#endif