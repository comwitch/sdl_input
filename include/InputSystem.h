#pragma once
#include "InputTypes.h"
#include <memory>
#include <unordered_map>
#include "Interface.h"
#include "Mapper.h"

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