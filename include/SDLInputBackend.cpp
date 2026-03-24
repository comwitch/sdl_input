#include "SDLInputBackend.h"
#include <SDL.h>
#include <cassert>
#include <stdio.h>

SDLInputBackend::SDLInputBackend() {
    
}

SDLInputBackend::~SDLInputBackend() {
    shutdown();
}

void SDLInputBackend::update() {
    if (!initialized_) 
    {
        return;
    }
    SDL_GameControllerUpdate();
}


std::vector<DeviceId> SDLInputBackend::getConnectedDevices() const {
    std::vector<DeviceId> ConnectedDevice;
    for (const auto& [id, device]:devices_)
    {
        if (SDL_GameControllerGetAttached(device.controller) == SDL_TRUE)
        {
            ConnectedDevice.push_back(id);
        }
    }
    return ConnectedDevice;
}

InputDeviceInfo SDLInputBackend::getDeviceInfo(DeviceId id) const {
    auto it = devices_.find(id);
    if (it == devices_.end())
    {
        //printf("No device attached");
        InputDeviceInfo Err = { id , "nothing", DeviceType::Unknown, "nothing", 0, 0, 0};
        return Err;
    }
    
    const SDLDevice& device = it->second;

    
    const char* name= SDL_GameControllerName(device.controller);
    std::string deviceName = name ? std::string(name) : std::string();
    
    // line check when debugging
    // DeviceType type=SDL_IsGameController(device.instanceId)?DeviceType::GameController:DeviceType::Joystick;
    DeviceType type=DeviceType::GameController;

    SDL_JoystickGUID guid = SDL_JoystickGetGUID(device.joystick); 
    char guidStr[33];
    SDL_JoystickGetGUIDString(guid, guidStr, sizeof(guidStr));
    int axisCount=SDL_JoystickNumAxes(device.joystick);
    int buttonCount=SDL_JoystickNumButtons(device.joystick);
    int hatCount=SDL_JoystickNumHats(device.joystick);

    InputDeviceInfo info={
        id,
        deviceName, // find method for checking 
        type, // type enum
        guidStr, // guid
        axisCount,
        buttonCount,
        hatCount    
    };

    return info;
}


bool SDLInputBackend::getRawState(DeviceId id, RawDeviceState& outState) const {
    

    auto it = devices_.find(id);
    if (it == devices_.end())
    {
        return false;
    }
        
    const SDLDevice& device = it->second;
    Sint16 lx = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 ly = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_LEFTY);
    Sint16 rx = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_RIGHTX);
    Sint16 ry = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_RIGHTY);
    Sint16 lt = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    Sint16 rt = SDL_GameControllerGetAxis(device.controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    Uint8 a = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_A);
    Uint8 b = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_B);
    Uint8 x = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_X);
    Uint8 y = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_Y);
    Uint8 lb = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    Uint8 rb = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    Uint8 back = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_BACK);
    Uint8 start = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_START);
    Uint8 leftStick = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
    Uint8 rightStick = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
    Uint8 dpadUp = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
    Uint8 dpadDown = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    Uint8 dpadLeft = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    Uint8 dpadRight = SDL_GameControllerGetButton(device.controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);


    outState.axes = {static_cast<float>(lx), static_cast<float>(ly), static_cast<float>(rx), static_cast<float>(ry), static_cast<float>(lt), static_cast<float>(rt)};
    outState.buttons = {static_cast<bool>(a), static_cast<bool>(b), static_cast<bool>(x), static_cast<bool>(y), static_cast<bool>(lb), static_cast<bool>(rb), static_cast<bool>(back), static_cast<bool>(start), static_cast<bool>(leftStick), static_cast<bool>(rightStick), static_cast<bool>(dpadUp), static_cast<bool>(dpadDown), static_cast<bool>(dpadLeft), static_cast<bool>(dpadRight)};
    outState.hats = {};

    return true;
    
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
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    initialized_ = false;
}
