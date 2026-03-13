#pragma once
#include "InputTypes.h"

class InputSystem {
public:
    explicit InputSystem(std::unique_ptr<IInputBackend> backend);

    bool initialize();
    void update();

    const GamepadState* getGamepadState(DeviceId id) const;
    std::vector<DeviceId> getConnectedGamepads() const;

private:
    std::unique_ptr<IInputBackend> backend_;

    struct DeviceContext {
        InputDeviceInfo info;
        RawDeviceState rawState;
        GamepadState gamepadState;
        DeviceMapper mapper;
    };

    std::unordered_map<DeviceId, DeviceContext> devices_;
};