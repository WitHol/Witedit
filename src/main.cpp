#include "header.h"
#include "terminal_windows/terminal_windows.h"
#include "key_detection/key_detection.h"
#include "file_management/file_management.h"

// ----------------------------------------------------------------------------
// The main function

bool end = false;

int globalCursorY;
int globalCursorX;

int main(int argc, char * argv[])
{
    // Ncurses setup
    initscr();
    refresh();

    // Configuring different windows
    EditorWindow mainWin(0, 0, LINES-3, COLS); // The main window for writing
    TextWindow helpWin(LINES-3, 0, LINES, COLS, false);

    // Checking, whether a path was provided
    if(argc < 2)
    {
        std::cout << "No file specified\n";
        return -1;
    }
 
    // Opening the file
    Wited_TextFile mainFile;
    mainFile.openFile(argv[1]);
    mainWin.buffer = mainFile.readFile();

    helpWin.buffer.push_back(L"  Press CTRL+Q to exit  |  Press CTRL+H for help");

    // Main loop
    while(true)
    {
        curs_set(0);

        helpWin.loop();
        mainWin.loop();

        move(globalCursorY, globalCursorX);
        curs_set(1);
        refresh();
        if(end) break;
    }

    mainFile.writeToFile(mainWin.buffer);
    mainFile.closeFile();

    // End
    endwin();
    return 0;
}