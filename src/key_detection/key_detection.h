/*
The whole purpose of detecting keys any other way than getch() is because
this method doesn't support some keys (like SHIFT, CTRL or ALT alone) and
detects function keys (like ENTER or arrows) as ctrl-some-key, which limits
possible hotkeys
*/


#ifndef KEY_DETECTION
#define KEY_DETECTION

#include "../header.h"
#include "key_definitions.h"
#include "../extras/extras.h"

class ModifierKeys
{
    public:
        bool shift;
        bool control;
        bool alt;
        
        bool lshift;
        bool lcontrol;
        bool lalt;
        
        bool rshift;
        bool rcontrol;
        bool ralt;

        ModifierKeys(bool shift = false, bool control_ = false, bool alt_ = false)
         : shift(shift), control(control), alt(alt) {}

        bool operator==(const ModifierKeys& other)
        {
            return shift == other.shift && control == other.control && alt == other.alt &&
                lshift == other.lshift && lcontrol == other.lcontrol && lalt == other.lalt &&
                rshift == other.rshift && rcontrol == other.rcontrol && ralt == other.ralt;
        }

        bool operator!=(const ModifierKeys& other)
        {
            return !(*this == other);
        }
};

std::vector<wchar_t> getPrintableKeys();

ModifierKeys getModifierKeys();

#endif