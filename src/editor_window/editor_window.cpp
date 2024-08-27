#include "editor_window.h"

// ----------------------------------------------------------------------------
// Constructor
EditorWindow::EditorWindow(int starty, int startx, int endy, int endx)
{
    window = newwin(endy-starty, endx-startx, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    keypad(window, TRUE);

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
            
            cchar_t ccharChar;
            attr_t ccharArtibutes;
            setcchar(&ccharChar, &buffer[i][j], ccharArtibutes, 0, (void *)0);
            mvwadd_wch(window, i+1, j+1, &ccharChar);
        }
    }

    wmove(window, cursorY-scrollY+1, cursorX-scrollX+1);
    wrefresh(window);
}

// ----------------------------------------------------------------------------
// A function, that gets user input and processes it.
void EditorWindow::processInput(std::vector<wchar_t> printableKeys, ModifierKeys modifierKeys)
{
    // These variable are for making the usual key typing pattern, where once a key is held,
    // it first types the char, waits for a short duration of time and starts spamming the char
    static std::vector<wchar_t> previousPrintableKeys;
    static ModifierKeys previousModifierKeys;
    static long previousClock;
    static uint8_t typingPhase;
    static int64_t cooldown;

    if(previousPrintableKeys != printableKeys || previousModifierKeys != modifierKeys) 
    {
        typingPhase = 0;
        cooldown = 0;
    }

    // If no keys are pressed or we're at a cooldown, there's no point in doing anything
    if(printableKeys.size() == 0) goto skip;
    if(cooldown > 0) goto skip;

    // Normal typing
    if(modifierKeys.shift == false && modifierKeys.control == false && modifierKeys.alt == false)
    {
        if(printableKeys[0] == K_ENTER) newLine(true);
        else if(printableKeys[0] == K_BACKSPACE) eraseChar();
        else if(printableKeys[0] == K_ARROW_RIGHT) moveCursor(DirEnum::RIGHT);
        else if(printableKeys[0] == K_ARROW_LEFT) moveCursor(DirEnum::LEFT);
        else if(printableKeys[0] == K_ARROW_UP) moveCursor(DirEnum::UP);
        else if(printableKeys[0] == K_ARROW_DOWN) moveCursor(DirEnum::DOWN);
        else typeChar(printableKeys[0]);
    }
    // Typing with shift
    else if (modifierKeys.shift == true && modifierKeys.control == false && modifierKeys.alt == false)
    {
        if(printableKeys[0] == K_ENTER) newLine(false);
        else if(printableKeys[0] == K_BACKSPACE) eraseChar();
        else typeChar(shiftedChar(printableKeys[0]));
    }
    // Keyboard shortcuts
    else
    {
        if(modifierKeys.control == true && modifierKeys.shift == false && modifierKeys.alt == false && printableKeys[0] == 'q')
            end = true;

        if(modifierKeys.control == true && modifierKeys.shift == false && modifierKeys.alt == false && printableKeys[0] == K_ENTER)
            newLine(false);
    }

    skip:

    if(typingPhase == 0)
    {
        typingPhase = 1;
        cooldown = FIRST_KEY_COOLDOWN;
    }
    else if(typingPhase == 1 && cooldown == 0) typingPhase = 2;
    else if(typingPhase == 2 && cooldown == 0) cooldown = SPAM_KEY_COOLDOWN;

    if(previousClock > clock()) previousClock = clock();
    cooldown = cooldown - (clock() - previousClock);
    if(cooldown < 0) cooldown = 0;


    previousPrintableKeys = printableKeys;
    previousModifierKeys = modifierKeys;
    previousClock = clock();

    writeToWindow();
}

// ----------------------------------------------------------------------------
// A function, that puts a desired char at cursor's position
void EditorWindow::typeChar(wchar_t key)
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
void EditorWindow::newLine(bool moveLine)
{
    std::wstring newLine;

    if(moveLine)
    {
        newLine.append(buffer[cursorY].substr(cursorX));
        buffer[cursorY].erase(buffer[cursorY].begin() + cursorX, buffer[cursorY].end());
    }

    buffer.insert(buffer.begin()+cursorY+1, newLine);
    
    cursorX = 0;
    cursorY += 1;
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
