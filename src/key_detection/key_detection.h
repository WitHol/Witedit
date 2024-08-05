/*
The whole purpose of detecting keys any other way than getch() is because
this method doesn't support some keys (like SHIFT, CTRL or ALT alone) and
detects function keys (like ENTER or arrows) as ctrl-some-key, which limits
possible hotkeys
*/


#ifndef KEY_DETECTION
#define KEY_DETECTION

#include "..\header.h"

std::vector<int> getKeys();

extern std::vector<int> printableChars;

#endif