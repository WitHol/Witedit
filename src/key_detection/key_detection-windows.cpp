// This method of detecting keys only works for windows
#ifdef _WIN64

#include "key_detection.h"

#include <windows.h>

std::vector<int> getPrintableKeys()
{
    static std::vector<int> pressedKeys;

    for(short i = 0x01; i < 0xfe; ++i)
    {
        if(i == K_SHIFT || i == K_CONTROL || i == K_HOME) continue;

        bool isKeyPressed = GetAsyncKeyState(i) & 0x8000;
        bool containsKey = contains(pressedKeys, i);

        if(isKeyPressed == containsKey) continue;

        if(isKeyPressed)
        {
            pressedKeys.insert(pressedKeys.begin(), i);
        }
        else
        {
            pressedKeys.erase(std::find(pressedKeys.begin(), pressedKeys.end(), i));
        }
    }

    return pressedKeys;
}

ModifierKeys getModifierKeys()
{
    ModifierKeys modifierKeys;

    if(GetAsyncKeyState(K_SHIFT) & 0x8000) modifierKeys.shift = true;
    if(GetAsyncKeyState(K_CONTROL) & 0x8000) modifierKeys.control = true;
    if(GetAsyncKeyState(K_HOME) & 0x8000) modifierKeys.alt = true;

    return modifierKeys;
}

#endif