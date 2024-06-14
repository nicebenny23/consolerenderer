#include "userinput.h"
#include <Windows.h>
#include "dynamicarray.h"
#include "Renderer.h"
DWORD userinput::newinputs = 0;
inpututil::inputkey keylist[256];
 inpututil::mouseinputstruct userinput::mousestate;
INPUT_RECORD inputEvents[15];

void userinput::initiate(){
    mousestate.pos = v2::zerov;
    memset(keylist, 0, sizeof(keylist));
    newinputs = 0;
}

inpututil::inputkey& userinput::Getkey(char keyval)
{
    if (keyval < 0 || keyval >= 256)
        return keylist[0];
    return keylist[static_cast<size_t>(keyval)];
}

\

void userinput::getinput(HANDLE hin)
{
    if (GetNumberOfConsoleInputEvents(hin, &newinputs) && newinputs > 0)
    {
        newinputs = 0;
        if (ReadConsoleInputW(hin, inputEvents, 8, &newinputs))
        {
            for (DWORD i = 0; i < newinputs; i++)
            {
                const auto& event = inputEvents[i];

                if (event.EventType == KEY_EVENT)
                {
                    char inputChar = event.Event.KeyEvent.uChar.AsciiChar;
                    bool keyDown = event.Event.KeyEvent.bKeyDown;

                    if (keyDown && !keylist[inputChar].held)
                        keylist[inputChar].onpressed();
                    else if (keylist[inputChar].held && !keyDown)
                        keylist[inputChar].onrelesed();
                }
                else if (event.EventType == MOUSE_EVENT)
                {
                    mousestate.pos = v2::Coordtovector(event.Event.MouseEvent.dwMousePosition)+v2::Vector2(-Render::GetDim().x/2, Render::GetDim().y / 2);
                }
            }
        }
    }
}

void userinput::resetkeys()
{
    for (DWORD i = 0; i < newinputs; i++)
    {
        const auto& event = inputEvents[i];

        if (event.EventType == KEY_EVENT)
        {
            char inputChar = event.Event.KeyEvent.uChar.AsciiChar;
            keylist[inputChar].resetkeyval();
        }
    }
}

