#include "file_management.h"

// ----------------------------------------------------------------------------
// A function, that opens the file stream
void Wited_TextFile::openFile(std::string path)
{
    // Checking if the file is openable
    file.open(path, std::ios::out);
    if(!file.is_open()) throw noOpenPermission();

    // Closing the file to re-open it in write mode and check, whether it is writable to
    file.close();
    file.open(path, std::ios::in | std::ios::out);
    if(!file.is_open()) throw noWritePermission();

    // If file writing is allowed, we can safely truncate the file
    file.close();
    file.open(path, std::ios::in | std::ios::out | std::ios::trunc);
}

// ----------------------------------------------------------------------------
// A function, for closing the file
void Wited_TextFile::closeFile()
{
    file.close();
}

// ----------------------------------------------------------------------------
// A function, that reads the file contents and returns themas a buffer
BUFFER Wited_TextFile::readFile()
{
    BUFFER buffer;

    std::wstring line;
    while(std::getline(file, line))
    {
        buffer.push_back(line);
    }
    if(buffer.size() == 0) buffer.push_back(std::wstring());

    return buffer;
}

// ----------------------------------------------------------------------------
// A function, which writes a buffer to a file
void Wited_TextFile::writeToFile(BUFFER buffer)
{
    for(int i = 0; i < buffer.size(); ++i)
    {
        std::cout << "1\n";
        file << buffer[i] << '\n';
        file << L"a\n";
    }
}