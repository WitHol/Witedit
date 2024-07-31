#include "header.h"
#include "tui_interface.h"

WINDOW * createWindow(int starty, int startx, int endy, int endx);
std::string readFile(std::string path);
void writeFile(std::string path, std::string buffer);
void resetCursorPos(WINDOW * win);
void moveCursor(WINDOW * win, int dir);
void deleteChar(WINDOW * win);
void writeToWindow(WINDOW * win, std::string buffer, int scrolledLines = 0);

constexpr inline int ctrl(char key){ return (key & 0x1f); }

// ----------------------------------------------------------------------------
// The main function

int main(int argc, char * argv[])
{
    // Creating the interface
    TUI_setup();

    // Configuring different windows
    TUI_EditorWindow mainWin(0, 0, LINES, COLS); // The main window for writing
    TUI_EditorWindow &currentWin = mainWin; // A reference to currently used window

    // Opening the file
    std::string path = "none.txt";
    std::vector<std::string> buffer = readFile(path);

    currentWin = mainWin;

    // Main loop
    while(true)
    {
        char input = getch();
        // Looping over special keys
        switch (input)
        {
            case ctrl('x'):
                goto end;
                break;

            case ctrl('g'):
                buffer.pop_back();
                break;

            default:
                buffer.push_back(input);
        }

        currentWin.writeToWindow(buffer, 0);
    }

    // End
    end:
    endwin();
    return 0;
}



// --------------------------------------------------------------------------
// A function for deleting characters
void deleteChar(WINDOW * win)
{
    int cursorY, cursorX;
    getyx(win, cursorY, cursorX);

    wmove(win, cursorY, cursorX-1);
    waddch(win, ' ');
    wmove(win, cursorY, cursorX-1);
}

// ----------------------------------------------------------------------------
// A function for putting all the text in a window
void writeToWindow(WINDOW * win, std::string buffer, int scrolledLines)
{
    int line = 0;
    int column = 0;

    for(char i : buffer)
    {
        if(i == (char)KEY_ENTER)
        {
            ++line;
            column = 0;
            continue;
        }

        if(line < scrolledLines || line >= getmaxy(win)-2 || column >= getmaxx(win)-2)
        {
            continue;
        }

        mvwaddch(win, line + 1, column - scrolledLines + 1, i);
        ++column;
    }
}

// ----------------------------------------------------------------------------
// File operation functions
std::string readFile(std::string path)
{
    std::string buffer;

    std::ifstream file (path, std::ios::out);
    if(!file.is_open())
    {
        std::printf("Failed to open the file\n");
        return buffer;
    } 

    std::string line;
    while ( std::getline(file, line))
    {
        buffer.append(line);
        buffer.push_back((char)KEY_ENTER);
    }

    file.close();
    return buffer;
}

void writeFile(std::string path, std::string buffer)
{
    std::ofstream file(path, std::ios::in | std::ios::ate);
    if(!file.is_open()) std::printf("Failed to write to the file");

    std::string line;
    for(int i = 0; i < buffer.size(); ++i)
    {
        if(buffer[i] == (char)KEY_ENTER)
        {
            file << line;
            continue;
        }

        line.push_back(buffer[i]);
    }
}