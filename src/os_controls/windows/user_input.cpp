#include "user_input.hpp"

#include <windows.h>

using biv::os::UserInput;

UserInput biv::os::get_user_input() {
    if (GetAsyncKeyState('D') & 0x8000) {
        return UserInput::MAP_LEFT;
    } else if (GetAsyncKeyState('A') & 0x8000) {
        return UserInput::MAP_RIGHT;
    } else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        return UserInput::MARIO_JUMP;
    } else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        return UserInput::EXIT;
    } else {
        return UserInput::NO_INPUT;
    }
}