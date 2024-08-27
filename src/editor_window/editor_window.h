/*
This is the header file for the EditorWindow class, 
which creates an ncurses window with editable text
*/

#ifndef EDITOR_WINDOW
#define EDITOR_WINDOW

#include "../header.h"
#include "../extras/extras.h"
#include "../key_detection/key_detection.h"

#define FIRST_KEY_COOLDOWN 500
#define SPAM_KEY_COOLDOWN 20

// A data type for the text buffer
typedef std::vector<std::wstring> BUFFER;

class EditorWindow
{
    public:
        BUFFER buffer;
        EditorWindow(int starty, int startx, int endy, int endx);
        void processInput(std::vector<wchar_t> printableKeys, ModifierKeys modifierKeys);

    private:
        WINDOW * window;

        int cursorY;
        int cursorX;

        signed int scrollY;
        signed int scrollX;

        void writeToWindow();
        void typeChar(wchar_t key);
        void eraseChar();
        void newLine(bool moveLine);
        void moveCursor(DirEnum dir);
};

#endif