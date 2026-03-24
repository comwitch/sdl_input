#include <SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    //std::cout << SDL_INIT_VIDEO << " " << SDL_INIT_GAMECONTROLLER << "\n";
    int num_joysticks = SDL_NumJoysticks();
    std::cout << "Number of joysticks: " << num_joysticks << std::endl;


    if (SDL_NumJoysticks() <= 0) {
        std::cout << "No controller found\n";
        SDL_Quit();
        return 0;
    }

    if (!SDL_IsGameController(0)) {
        std::cout << "Device 0 is not a game controller\n";
        SDL_Quit();
        return 0;
    }

    SDL_GameController* pad = SDL_GameControllerOpen(0);
    if (!pad) {
        std::cerr << "SDL_GameControllerOpen failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 300; ++i) {
        SDL_GameControllerUpdate();

        Sint16 lx = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX);
        Sint16 ly = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY);
        Uint8 a   = SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A);
        Uint8 b   = SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B);
        Uint8 x=SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X);
        int axisCount=SDL_JoystickNumAxes(SDL_GameControllerGetJoystick(pad));
        int buttonCount=SDL_JoystickNumButtons(SDL_GameControllerGetJoystick(pad));
        int hatCount=SDL_JoystickNumHats(SDL_GameControllerGetJoystick(pad));

        std::cout << "LX=" << lx
                  << " LY=" << ly
                  << " A=" << (int)a
                  << " B=" << (int)b
                  << "static casting lx= " << static_cast<float>(lx) / 32768.0f
                  << "static casting ly= " << static_cast<float>(ly) / 32768.0f
                  // << "axisCount=" << axisCount
                  // << " buttonCount=" << buttonCount
                  // << " hatCount=" << hatCount
                  << "\n";

        if (x != 0){
            std::cout << "X button pressed!\n";
            SDL_Quit();
            return 0;
        }

        
        SDL_Delay(100);
    }

    SDL_GameControllerClose(pad);
    SDL_Quit();
    return 0;
}