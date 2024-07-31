#include "tui_interface.h"
#include "header.h"

// ----------------------------------------------------------------------------
// Constructor
TUI_EditorWindow::TUI_EditorWindow(int starty, int startx, int endy, int endx, std::vector<std::string> buffer)
{
    window = newwin(endy - starty, endx - startx, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    keypad(window, FALSE);
}

// ----------------------------------------------------------------------------
// A function for writing buffer contents into the window
void TUI_EditorWindow::writeToWindow(int scrolledLines)
{
    int line = 0;
    int column = 0;

    for(std::string i : buffer)
    {
        if(line < scrolledLines || line >= getmaxy(window)+scrolledLines-2) continue;

        for(char j : i)
        {
        if(column >= getmaxx(window)-2) continue;

        mvwaddch(window, line + 1, column - scrolledLines + 1, j);
        ++column;
        }

        ++line;
    }

    wrefresh(window);
}

// ----------------------------------------------------------------------------
// A function for moving the cursor around
void TUI_EditorWindow::moveCursor(int dir)
{
    switch(dir)
    {
        case 1:
            cursorY -= 1;
            break;
        case 2:
            cursorX += 1;
            break;
        case 3:
            cursorY += 1;
            break;
        case 4:
            cursorX -= 1;
            break;
    }

    resetCursorPos();
}

// ----------------------------------------------------------------------------
// A function for putting the cursot in a specific place
void TUI_EditorWindow::setCursorPos(int y, int x)
{
    cursorY = y;
    cursorX = x;

    resetCursorPos();
}

// ----------------------------------------------------------------------------
// A function, that resets the cursor pos, so that it doesn't break the border
void TUI_EditorWindow::resetCursorPos()
{
    if(cursorY < 1) cursorY = 1;
    if(cursorX < 1) cursorX = 1;
    if(cursorX-1 > buffer[cursorY-1].length()) cursorX=buffer[cursorY-1].length();

    wmove(window, cursorY, cursorX);
}
