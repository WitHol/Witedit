/*
This is the header file for the EditorWindow class, 
which creates an ncurses window with editable text
*/

#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "../header.h"

// A data type for the text buffer
typedef std::vector<std::string> BUFFER;

void setupInterface();

void killInterface();


class EditorWindow
{
    public:
        BUFFER buffer;
        EditorWindow(int starty, int startx, int endy, int endx);
        void processInput(std::vector<int> keys);

    private:
        WINDOW * window;

        int cursorY;
        int cursorX;

        signed int scrollY;
        signed int scrollX;

        void writeToWindow();
        void typeChar(int key);
        void eraseChar();
        void newLine();
        void moveCursor(DirEnum dir);
};

#endif