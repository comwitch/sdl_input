#include "SDLInputBackend.h"
#include <SDL.h>
#include <stdio.h>

void SDLInputBackend::SDLInputBackend() {
    SDLInputBackend::initialize();
}

void SDLInputBackend::~SDLInputBackend() {
    SDLInputBackend::shutdown();
}

void SDLInputBackend::update() {
    if (!initialized_) 
    {
        return;
    }
    SDL_GameControllerUpdate();
}

bool SDLInputBackend::getRawState(DeviceId id, RawDeviceState& outState) const {
    return false;
}

bool SDLInputBackend::initialize() {
    if (initialized_) 
    {
        return true;
    }

    if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0)
    {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    else 
    {
        int num_controllers = SDL_NumJoysticks();
        for (int i = 0; i < num_controllers; i++)
        {
            if (SDL_IsGameController(i))
            {
                SDL_GameController* controller = SDL_GameControllerOpen(i);
                assert(controller);
                SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
                assert(joystick);
                SDL_JoystickID instanceId = SDL_JoystickInstanceID(joystick);
                DeviceId id=nextDeviceId_++;
                devices_[id] = {id, controller, joystick, instanceId};
            }
        }
    }
    initialized_ = true;
    return true;
}

void SDLInputBackend::shutdown() {
    if (!initialized_) 
    {
        return;
    }

    for (auto& [id, device] : devices_) 
    {
        if (device.controller) 
        {
            SDL_GameControllerClose(device.controller);
            device.controller = nullptr;
        }
    }
    
    devices_.clear();
    SDL_Quit();
    initialized_ = false;
}