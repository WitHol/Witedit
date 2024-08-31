#include "terminal_windows.h"

// ----------------------------------------------------------------------------
// Constructor
EditorWindow::EditorWindow(int starty, int startx, int endy, int endx, int rightMargin, int leftMargin, int topMargin, int bottomMargin)
{
    window = newwin(endy-starty, endx-startx, starty, startx);
    box(window, 0, 0);
    //wrefresh(window);
    keypad(window, TRUE);

    (*this).rightMargin = rightMargin;
    (*this).leftMargin = leftMargin;
    (*this).topMargin = topMargin;
    (*this).bottomMargin = bottomMargin;

    render();
}

// ----------------------------------------------------------------------------
// The main loop function
void EditorWindow::loop()
{
    processInput();
    render();
    wrefresh(window);

    globalCursorY = cursorY + topMargin + 1;
    globalCursorX = cursorX + rightMargin + 1;
}

// ----------------------------------------------------------------------------
// A function for writing buffer contents into the window
void EditorWindow::render()
{
    for(int i = scrollY; i < getmaxy(window) + scrollY - topMargin - bottomMargin - 2; ++i)
    {
        for(int j = scrollX; j < getmaxx(window) + scrollX - rightMargin - leftMargin - 2; ++j)
        {
            int currentY = i - scrollY + topMargin + 1;
            int currentX = j - scrollX + rightMargin + 1;

            if(buffer.size() <= i || buffer[i].size() <= j)
            {
                mvwaddch(window, currentY, currentX, ' ');
                continue;
            }

            cchar_t ccharChar;
            attr_t ccharArtibutes;
            setcchar(&ccharChar, &buffer[i][j], ccharArtibutes, 0, (void *)0);
            mvwadd_wch(window, currentY, currentX, &ccharChar);
        }
    }
}

// ----------------------------------------------------------------------------
// A function, that gets user input and processes it.
void EditorWindow::processInput()
{
    std::vector<wchar_t> printableKeys = getPrintableKeys();
    ModifierKeys modifierKeys = getModifierKeys();

    // This code is for making the usual key typing pattern, where once a key is held,
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
        else if(printableKeys[0] == K_DELETE) { moveCursor(DirEnum::RIGHT); eraseChar(); }
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
        if(modifierKeys.control && !modifierKeys.shift && !modifierKeys.alt && printableKeys[0] == K_ARROW_UP) moveView(DirEnum::UP);
        if(modifierKeys.control && !modifierKeys.shift && !modifierKeys.alt && printableKeys[0] == K_ARROW_DOWN) moveView(DirEnum::DOWN);

        if(modifierKeys.control && !modifierKeys.shift && !modifierKeys.alt && printableKeys[0] == 'q')
            end = true;

        if(modifierKeys.control && !modifierKeys.shift && !modifierKeys.alt && printableKeys[0] == K_ENTER)
            newLine(false);
    }

    skip:

    // Key typing pattern code
    if(typingPhase == 0) {typingPhase = 1; cooldown = FIRST_KEY_COOLDOWN;}
    else if(typingPhase == 1 && cooldown == 0) typingPhase = 2;
    else if(typingPhase == 2 && cooldown == 0) cooldown = SPAM_KEY_COOLDOWN;
    if(previousClock > clock()) previousClock = clock();
    cooldown = cooldown - (clock() - previousClock);
    if(cooldown < 0) cooldown = 0;

    previousPrintableKeys = printableKeys;
    previousModifierKeys = modifierKeys;
    previousClock = clock();
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

// ----------------------------------------------------------------------------
// A function for moving the viwe (scrolling)
void EditorWindow::moveView(DirEnum dir)
{
    if(dir == DirEnum::RIGHT) ++scrollX;
    else if(dir == DirEnum::LEFT && scrollX > 0) --scrollX;
    else if(dir == DirEnum::UP && scrollY > 0) -- scrollY;
    else if(dir == DirEnum::DOWN) ++scrollY;
}
