#include "InputSystem.h"
#include "SDLInputBackend.h"
#include <SDL.h>

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main() {
    auto backend = std::make_unique<SDLInputBackend>();
    InputSystem inputSystem(std::move(backend));
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    if (SDL_NumJoysticks() <= 0) {
        std::cout << "No controller found\n";
        SDL_Quit();
        return 0;
    }



    std::cout << "InputSystem test start\n";
    
    while (true) {
        inputSystem.update();

        auto ids = inputSystem.getConnectedGamepads();
        for (auto id : ids) {
            const GamepadState* state = inputSystem.getGamepadState(id);
            if (!state) continue;

            std::cout
                << "id=" << id
                << " LX=" << state->leftStickX
                << " LY=" << state->leftStickY
                << " A=" << state->south
                << " B=" << state->east
                << "\n";

            if (state->west) {
                std::cout << "Right stick moved! Exiting...\n";
                SDL_Quit();
                return 0;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}