// This method of detecting keys only works for windows
#ifdef _WIN64

#include "key_detection.h"

#include <windows.h>

// A function for mapping keys from windows VK codes to Unicode chars
int mapKey(const int &virtualKey)
{
    const static std::pair<wchar_t, wchar_t> keysMap[] = {
        // Mapping windows oddities to Unicode
        {VK_OEM_COMMA, ','},
        {VK_OEM_MINUS, '-'}, 
        {VK_OEM_PERIOD, '.'},
        {VK_OEM_2, '/'},
        {VK_OEM_5, '\\'},
        {VK_OEM_1, ';'},
        {VK_OEM_PLUS, '='},
        {VK_OEM_4, '['},
        {VK_OEM_6, ']'},

        // Baisically renames
        {VK_RETURN, K_ENTER},
        {VK_BACK, K_BACKSPACE},

        // Letters to lowercase
        {'A', 'a'},
        {'B', 'b'},
        {'C', 'c'},
        {'D', 'd'},
        {'E', 'e'},
        {'F', 'f'},
        {'G', 'g'},
        {'H', 'h'},
        {'I', 'i'},
        {'J', 'j'},
        {'K', 'k'},
        {'L', 'l'},
        {'M', 'm'},
        {'N', 'n'},
        {'O', 'o'},
        {'P', 'p'},
        {'Q', 'q'},
        {'R', 'r'},
        {'S', 's'},
        {'T', 't'},
        {'U', 'u'},
        {'V', 'v'},
        {'W', 'w'},
        {'X', 'x'},
        {'Y', 'y'},
        {'Z', 'z'}
    };

    for(const std::pair<int, int> &keyPair : keysMap)
    {
        if(keyPair.first == virtualKey)
        {
            return keyPair.second;
        }
    }

    return virtualKey;
}

std::vector<wchar_t> getPrintableKeys()
{
    static std::vector<wchar_t> pressedKeys;
    static bool virtualPressedKeys[0xff];

    for(short i = 0x01; i < 0xff; ++i)
    {
        wchar_t mappedKey = mapKey(i);

        bool isKeyPressed = GetAsyncKeyState(i) & 0x8000;
        bool containsKey = virtualPressedKeys[i];

        if(isKeyPressed == containsKey) continue;
        if(mappedKey == 0x0000) continue;

        if(isKeyPressed)
        {
            virtualPressedKeys[i] = true;
            pressedKeys.insert(pressedKeys.begin(), mappedKey);
        }
        else
        {
            virtualPressedKeys[i] = false;
            pressedKeys.erase(std::find(pressedKeys.begin(), pressedKeys.end(), mappedKey));
        }
    }

    return pressedKeys;
}

ModifierKeys getModifierKeys()
{
    ModifierKeys modifierKeys;

    modifierKeys.shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
    modifierKeys.control = GetAsyncKeyState(VK_CONTROL) & 0x8000;
    modifierKeys.alt = GetAsyncKeyState(VK_MENU) & 0x8000;

    modifierKeys.lshift = GetAsyncKeyState(VK_LSHIFT) & 0x8000;
    modifierKeys.lcontrol = GetAsyncKeyState(VK_LCONTROL) & 0x8000;
    modifierKeys.lalt = GetAsyncKeyState(VK_LMENU) & 0x8000;

    modifierKeys.rshift = GetAsyncKeyState(VK_RSHIFT) & 0x8000;
    modifierKeys.rcontrol = GetAsyncKeyState(VK_RCONTROL) & 0x8000;
    modifierKeys.ralt = GetAsyncKeyState(VK_RMENU) & 0x8000;

    return modifierKeys;
}

#endif