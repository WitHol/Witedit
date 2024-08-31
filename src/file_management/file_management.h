#ifndef FILE_MANAGER
#define FILE_MANAGER

#include "../header.h"

// The class for easy management of text files
class Wited_TextFile
{
    public:
        void openFile(std::string path);
        void closeFile();
        BUFFER readFile();
        void writeToFile(BUFFER buffer);
    private:
        std::wfstream file;
};

// Exceptions thrown, when the file is unable to be opened or read-only
class noWritePermission : std::exception
{
    public:
        std::string message = "No permission to write to the file";
};
class noOpenPermission : std::exception
{
    public:
        std::string message = "No permission to open the file";
};

#endif