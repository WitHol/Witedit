#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "header.h"


void setupInterface();

void killInterface();


class EditorWindow
{
    public:
        BUFFER buffer;
        EditorWindow(int starty, int startx, int endy, int endx);
        void processInput(wchar_t);

    private:
        WINDOW * window;

        int cursorY;
        int cursorX;

        signed int scrollY;
        signed int scrollX;

        void writeToWindow();
        void typeChar(wchar_t key);
        void eraseChar();
        void newLine();
        void moveCursor(int dir);
};

#endif