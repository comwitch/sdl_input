#pragma once
#include "Interface.h"
#include <SDL.h>
#include <unordered_map>



class SDLInputBackend : public IInputBackend {
public:
    SDLInputBackend();
    ~SDLInputBackend() override;

    bool initialize() override;
    void shutdown() override;
    void update() override;

    std::vector<DeviceId> getConnectedDevices() const override;
    InputDeviceInfo getDeviceInfo(DeviceId id) const override;
    bool getRawState(DeviceId id, RawDeviceState& outState) const override;
    
private:
    struct SDLDevice 
    {
       DeviceId id;
       SDL_GameController* controller = nullptr;
       SDL_Joystick* joystick = nullptr;
       SDL_JoystickID instanceId = -1;
    };

    struct

    std::unordered_map<DeviceId, SDLDevice> devices_;
    int nextDeviceId_ = 0;
    bool initialized_ = false;

};

