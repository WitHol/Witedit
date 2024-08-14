#include "header.h"
#include "editor_window/editor_window.h"
#include "key_detection/key_detection.h"

BUFFER readFile(std::string path);
void writeFile(std::string path, std::string buffer);

// ----------------------------------------------------------------------------
// The main function

bool end = false;

int main(int argc, char * argv[])
{
    // Creating the interface
    setupInterface();

    // Configuring different windows
    EditorWindow mainWin(0, 0, LINES, COLS); // The main window for writing

    // Opening the file
    std::string path = "none.txt";
    //mainWin.buffer = readFile(path);

    // Main loop
    while(true)
    {
        mainWin.processInput(getPrintableKeys(), getModifierKeys());

        if(end) break;
    }

    // End
    killInterface();
    return 0;
}


// ----------------------------------------------------------------------------
// File operation functions
BUFFER readFile(std::string path)
{
    BUFFER buffer;

    std::wifstream file (path, std::ios::out);

    if(!file.is_open())
    {
        std::cout << "Failed to open the file\n";
        return buffer;
    } 

    std::wstring line;
    while(std::getline(file, line))
    {
        buffer.push_back(line);
    }

    file.close();
    return buffer;
}

void writeFile(std::string path, BUFFER buffer)
{
    std::wofstream file(path, std::ios::in | std::ios::ate);

    if(!file.is_open())
    {
        std::printf("Failed to write to the file");
        return;
    }

    std::wstring line;
    for(int i = 0; i < buffer.size(); ++i)
    {
        file << line;
        continue;
    }
}