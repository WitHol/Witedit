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

// Including necessary files inside of the project
#include "extras/extras.h"

// A data type for the text buffer
typedef std::vector<std::wstring> BUFFER;

// This is for stopping the program
extern bool end;

// Objective cursor position is needed
extern int globalCursorY;
extern int globalCursorX;

// Definitions for all the needed keys, mostly stolen from <windows.h>
#define K_LBUTTON 0x01
#define K_RBUTTON 0x02
#define K_TAB 0x09
#define K_SHIFT 0x10
#define K_CONTROL 0x11
#define K_MENU 0x12
#define K_ESCAPE 0x1B
#define K_SPACE 0x20
#define K_HOME 0x24
#define K_INSERT 0x2D
#define K_DELETE 0x2E
#define K_LSHIFT 0xA0
#define K_RSHIFT 0xA1
#define K_LCONTROL 0xA2
#define K_RCONTROL 0xA3
#define K_LMENU 0xA4
#define K_RMENU 0xA5
#define K_ENTER 0x000D
#define K_BACKSPACE 0x0008
#define K_ARROW_RIGHT 0x0025
#define K_ARROW_LEFT 0x0027
#define K_ARROW_UP 0x0026
#define K_ARROW_DOWN 0x0028

#endif