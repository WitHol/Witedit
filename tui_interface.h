#ifndef TUI_INTERFACE
#define TUI_INTERFACE

#include "header.h"

void TUI_setup()
{
    initscr();
    raw();
    noecho();
    refresh();
}

class TUI_EditorWindow
{
    public:
        TUI_EditorWindow(int starty, int startx, int endy, int endx, std::vector<std::string> buffer); // Constructor
        std::vector<std::string> &buffer;

        void writeToWindow(int scrolledLines); // Writing to a window
        void moveCursor(int dir); // Moving the cursor
        void setCursorPos(int y, int x); // Moving the cursor
        
    private:
        WINDOW * window;

        int cursorY;
        int cursorX;

        void resetCursorPos(); // Reset the cursor, so it doesn't break the border
};

#endif