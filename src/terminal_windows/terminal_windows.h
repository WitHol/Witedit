/*
This is the header file for the EditorWindow class, 
which creates an ncurses window with editable text
*/

#ifndef TERMINAL_WINDOWS
#define TERMINAL_WINDOWS

#include "../header.h"
#include "../key_detection/key_detection.h"

#define FIRST_KEY_COOLDOWN 500
#define SPAM_KEY_COOLDOWN 20

// The winddow with editable text
class EditorWindow
{
    public:
        int leftMargin;
        int rightMargin;
        int topMargin;
        int bottomMargin;

        void loop();
        BUFFER buffer;
        EditorWindow(int starty, int startx, int endy, int endx, int rightMargin = 0, int leftMargin = 0, int topMargin = 0, int bottomMargin = 0);

    private:
        WINDOW * window;

        int cursorY = 0;
        int cursorX = 0;

        signed int scrollY = 0;
        signed int scrollX = 0;

        void processInput();
        void render();
        void typeChar(wchar_t key);
        void eraseChar();
        void newLine(bool moveLine);
        void moveCursor(DirEnum dir);
        void moveView(DirEnum dir);
};


// A stripped-down version of the editor window, that can only display text
class TextWindow
{
    public:
        bool isScrollable;

        int leftMargin;
        int rightMargin;
        int topMargin;
        int bottomMargin;

        signed int scrollY = 0;
        signed int scrollX = 0;

        void loop();
        BUFFER buffer;
        TextWindow(int starty, int startx, int endy, int endx, bool isScrollable, int rightMargin = 0, int leftMargin = 0, int topMargin = 0, int bottomMargin = 0);
    private:
        WINDOW * window;

        void render();
        void processInput();
        void moveView(DirEnum dir);
};

#endif