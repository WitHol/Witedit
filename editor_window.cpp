#include "editor_window.h"
#include "header.h"

// ----------------------------------------------------------------------------
// Out-of-class functions for starting and ending ncurses mode
void setupInterface()
{
    initscr();
    raw();
    noecho();
    refresh();
}

void killInterface()
{
    endwin();
}

// ----------------------------------------------------------------------------
// Constructor
EditorWindow::EditorWindow(int starty, int startx, int endy, int endx)
{
    window = newwin(endy-starty, endx-startx, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    keypad(window, TRUE);

    std::string emptyString = "";
    buffer.push_back(emptyString);

    cursorX = 0;
    cursorY = 0;

    scrollX = 0;
    scrollY = 0;

    writeToWindow();
}

// ----------------------------------------------------------------------------
// A function for writing buffer contents into the window
void EditorWindow::writeToWindow()
{
    int line = 0;
    int column = 0;

    for(int i = scrollY; i < getmaxy(window)+scrollY-2; ++i)
    {
        for(int j = scrollX; j < getmaxx(window)+scrollX-2; ++j)
        {
            if(buffer.size() <= i)
            {
                mvwaddch(window, i+1, j+1, ' ');
                break;
            }

            if(buffer[i].size() <= j)
            {
                mvwaddch(window, i+1, j+1, ' ');
                break;
            }
            
            mvwaddch(window, i+1, j+1, buffer[i][j]);
        }
    }

    wmove(window, cursorY-scrollY+1, cursorX-scrollX+1);
    wrefresh(window);
}

// ----------------------------------------------------------------------------
// A function, that gets user input and processes it.
void EditorWindow::processInput(wchar_t input)
{
    // Looping over keys
    switch (input)
    {
        case CTRL('q'):
            end = true;
            break;

        case KEY_BACKSPACE:
            eraseChar();
            break;

        case KEY_UP:
            moveCursor(1);
            break;
        
        case CTRL('j'):
            newLine();
            break;

        case KEY_RIGHT:
            moveCursor(2);
            break;

        case KEY_DOWN:
            moveCursor(3);
            break;

        case KEY_LEFT:
            moveCursor(4);
            break;

        default:
            typeChar(input);
    }

    writeToWindow();
}

// ----------------------------------------------------------------------------
// A function, that puts a desired char at cursor's position
void EditorWindow::typeChar(wchar_t key)
{
    if(key == CTRL(key)) return;

    buffer[cursorY].insert(cursorX, 1, key);
    moveCursor(2);
}

// ----------------------------------------------------------------------------
// A function, that removes a char once backspace was pressed
void EditorWindow::eraseChar()
{
    if(cursorX == 0 && cursorY == 0) return;

    if(cursorX == 0)
    {
        moveCursor(4);
        buffer[cursorY].append(buffer[cursorY+1]);
        buffer.erase(buffer.begin() + cursorY + 1);
    }
    else
    {
        buffer[cursorY].erase(cursorX-1, 1);
        moveCursor(4);
    }
}

// ----------------------------------------------------------------------------
// A function, that adds a new line after the one cursor is at
void EditorWindow::newLine()
{
    std::string emptyString = "";
    buffer.insert(buffer.begin()+cursorY+1, emptyString);
    cursorX = 0;
    ++cursorY;
}

// ----------------------------------------------------------------------------
// A function for moving the cursor around
void EditorWindow::moveCursor(int dir)
{
    switch(dir)
    {
        case 1:
            if(cursorY == 0 && cursorX == 0) break;

            if(cursorY == 0 && cursorX > 0)
            {
                cursorX = 0;
                break;
            }

            if(cursorX > buffer[cursorY-1].size())
            {
                cursorX = buffer[cursorY-1].size();
            }

            --cursorY;
            break;

        case 2:
            if(cursorX == buffer[cursorY].size() && cursorY == buffer.size()-1) break;

            if(cursorX == buffer[cursorY].size() && cursorY < buffer.size()-1)
            {
                cursorX = 0;
                cursorY += 1;
                break;
            }

            ++cursorX;
            break;

        case 3:
            if(cursorY == buffer.size()-1) 
            {
                cursorX = buffer[cursorY].size();
                break;
            }

            if(cursorX > buffer[cursorY+1].size())
            {
                cursorX = buffer[cursorY+1].size();
            }

            ++cursorY;
            break;

        case 4:
            if(cursorX == 0 && cursorY == 0) break;

            if(cursorX == 0 && cursorY > 0)
            {
                --cursorY;
                cursorX = buffer[cursorY].size();
                break;
            }

            --cursorX;
            break;
    }
}
