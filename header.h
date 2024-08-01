#ifndef HEADER
#define HEADER

#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

#define BUFFER std::vector<std::string>
#define CTRL(key) ((key) & 0x1f)

extern bool end;

#endif