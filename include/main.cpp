#include <SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    int n = SDL_NumJoysticks();
    std::cout << "num devices = " << n << "\n";

    for (int i = 0; i < n; ++i) {
        const char* joyName = SDL_JoystickNameForIndex(i);
        std::cout << "index " << i
                  << " name=" << (joyName ? joyName : "(unknown)")
                  << " isGameController=" << SDL_IsGameController(i)
                  << "\n";
    }

    SDL_Quit();
    return 0;
}