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
    keypad(stdscr, TRUE);
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
void EditorWindow::processInput(std::vector<int> keys)
{
    static std::vector<int> previousKeys;
    static unsigned long int waitingTime = 0;


    if(waitingTime && keys == previousKeys) goto skip;
    else waitingTime = 0;

    if(keys.size() == 0) goto skip;

    if(!contains(keys, K_CONTROL) && !contains(keys, K_HOME) && !contains(keys, K_SHIFT))
    {
        typeChar(keys[0]);
    }
    if(!contains(keys, K_CONTROL) && !contains(keys, K_HOME) && contains(keys, K_SHIFT))
    {
        !contains(printableChars, keys[0]);
        typeChar(keys[0] + ('A' - 'a'));
    }

    skip:

    if(waitingTime > 0)
    {
        --waitingTime;
        _sleep(1);
    }

    previousKeys = keys;

    writeToWindow();
}

// ----------------------------------------------------------------------------
// A function, that puts a desired char at cursor's position
void EditorWindow::typeChar(int key)
{
    buffer[cursorY].insert(cursorX, 1, key);
    moveCursor(DirEnum::RIGHT);
}

// ----------------------------------------------------------------------------
// A function, that removes a char once backspace was pressed
void EditorWindow::eraseChar()
{
    if(cursorX == 0 && cursorY == 0) return;

    if(cursorX == 0)
    {
        moveCursor(DirEnum::LEFT);
        buffer[cursorY].append(buffer[cursorY+1]);
        buffer.erase(buffer.begin() + cursorY + 1);
    }
    else
    {
        buffer[cursorY].erase(cursorX-1, 1);
        moveCursor(DirEnum::LEFT);
    }
}

// ----------------------------------------------------------------------------
// A function, that adds a new line after the one cursor is at
void EditorWindow::newLine()
{
    std::string emptyString = "";
    buffer.insert(buffer.begin()+cursorY+1, emptyString);
    cursorX = 0;
    moveCursor(DirEnum::DOWN);
}

// ----------------------------------------------------------------------------
// A function for moving the cursor around
void EditorWindow::moveCursor(DirEnum dir)
{
    switch(dir)
    {
        case DirEnum::UP:
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

        case DirEnum::RIGHT:
            if(cursorX == buffer[cursorY].size() && cursorY == buffer.size()-1) break;

            if(cursorX == buffer[cursorY].size() && cursorY < buffer.size()-1)
            {
                cursorX = 0;
                cursorY += 1;
                break;
            }

            ++cursorX;
            break;

        case DirEnum::DOWN:
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

        case DirEnum::LEFT:
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
