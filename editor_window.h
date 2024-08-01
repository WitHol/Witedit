#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "header.h"


void setupInterface();

void killInterface();


class EditorWindow
{
    public:
        EditorWindow(int starty, int startx, int endy, int endx);
        BUFFER buffer;

        void writeToWindow();
        void processInput();

    private:
        WINDOW * window;

        int cursorY;
        int cursorX;

        signed int scrollY;
        signed int scrollX;

        void typeChar(wchar_t key);
        void eraseChar();
        void newLine();
        void moveCursor(int dir);
};

#endif