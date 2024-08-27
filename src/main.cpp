#include "header.h"
#include "editor_window/editor_window.h"
#include "key_detection/key_detection.h"

BUFFER readFile(std::string path);
void writeFile(std::string path, BUFFER buffer);

// ----------------------------------------------------------------------------
// The main function

bool end = false;

int main(int argc, char * argv[])
{
    // Ncurses setup
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    // Configuring different windows
    EditorWindow mainWin(0, 0, LINES, COLS); // The main window for writing

    // Opening the file
    if(argc < 2)
    {
        std::cout << "No file specified";
        return -1;
    }
    std::string path = argv[1];
    mainWin.buffer = readFile(path);

    // Main loop
    while(true)
    {
        mainWin.processInput(getPrintableKeys(), getModifierKeys());

        if(end) break;
    }

    writeFile(path, mainWin.buffer);

    // End
    endwin();
    return 0;
}


// ----------------------------------------------------------------------------
// File operation functions
BUFFER readFile(std::string path)
{
    BUFFER buffer;

    std::wifstream fileStream(path, std::ios::out);

    if(!fileStream.is_open())
    {
        std::cout << "Failed to open the file\n";
        return buffer;
    } 

    std::wstring line;
    while(std::getline(fileStream, line))
    {
        buffer.push_back(line);
    }
    if(buffer.size() == 0) buffer.push_back(std::wstring());

    fileStream.close();
    return buffer;
}

void writeFile(std::string path, BUFFER buffer)
{
    std::wofstream fileStream(path, std::ios::in | std::ios::trunc);

    if(!fileStream.is_open())
    {
        std::printf("Failed to write to the file");
        return;
    }

    for(int i = 0; i < buffer.size(); ++i)
    {
        fileStream << buffer[i] << '\n';
    }
}