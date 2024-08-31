#include "terminal_windows.h"

// ----------------------------------------------------------------------------
// Constructor
TextWindow::TextWindow(int starty, int startx, int endy, int endx, bool isScrollable, int rightMargin, int leftMargin, int topMargin, int bottomMargin)
{
    window = newwin(endy-starty, endx-startx, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    keypad(window, TRUE);

    (*this).rightMargin = rightMargin;
    (*this).leftMargin = leftMargin;
    (*this).topMargin = topMargin;
    (*this).bottomMargin = bottomMargin;
    (*this).isScrollable = isScrollable;

    render();
}

// ----------------------------------------------------------------------------
// The main loop function
void TextWindow::loop()
{
    render();
    if(isScrollable) processInput();
    wrefresh(window);
}

// ----------------------------------------------------------------------------
// A function for rendering the text
void TextWindow::render()
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
// A function for processing arrows to scroll the text
void TextWindow::processInput()
{
    std::vector<wchar_t> printableKeys = getPrintableKeys();

    // This code is for making the usual key typing pattern, where once a key is held,
    // it first types the char, waits for a short duration of time and starts spamming the char
    static std::vector<wchar_t> previousPrintableKeys;
    static long previousClock;
    static uint8_t typingPhase;
    static int64_t cooldown;

    if(previousPrintableKeys != printableKeys) 
    {
        typingPhase = 0;
        cooldown = 0;
    }

    if(cooldown <= 0)
    {
        if(printableKeys[0] == K_ARROW_RIGHT) moveView(DirEnum::RIGHT);
        if(printableKeys[0] == K_ARROW_LEFT) moveView(DirEnum::LEFT);
        if(printableKeys[0] == K_ARROW_UP) moveView(DirEnum::UP);
        if(printableKeys[0] == K_ARROW_DOWN) moveView(DirEnum::DOWN);
    }

    // Key typing pattern code
    if(typingPhase == 0) {typingPhase = 1; cooldown = FIRST_KEY_COOLDOWN;}
    else if(typingPhase == 1 && cooldown == 0) typingPhase = 2;
    else if(typingPhase == 2 && cooldown == 0) cooldown = SPAM_KEY_COOLDOWN;
    if(previousClock > clock()) previousClock = clock();
    cooldown = cooldown - (clock() - previousClock);
    if(cooldown < 0) cooldown = 0;

    previousPrintableKeys = printableKeys;
    previousClock = clock();
}

// ----------------------------------------------------------------------------
// A function for scrolling the texts
void TextWindow::moveView(DirEnum dir)
{
    if(dir == DirEnum::RIGHT) ++scrollX;
    else if(dir == DirEnum::LEFT && scrollX > 0) --scrollX;
    else if(dir == DirEnum::UP && scrollY > 0) -- scrollY;
    else if(dir == DirEnum::DOWN) ++scrollY;
}