#include "InputSystem.h"

InputSystem::InputSystem(std::unique_ptr<IInputBackend> backend)
    : backend_(std::move(backend)) {
        if (!initialize()) {
            printf("Failed to initialize InputSystem\n");
            return;
        }
    }

bool InputSystem::initialize() {
    if (!backend_->initialize()) 
    {
        return false;
    }

    if (!devices_.empty()) 
    {
        return true;
    }

    for (DeviceId id : backend_->getConnectedDevices()) 
     {
        InputDeviceInfo info = backend_->getDeviceInfo(id);
        devices_[id] = DeviceContext{info, {}, {}, DeviceMapper()};
        devices_[id].mapper.setSDLDefaultMapping();
    }

    return true;
}

void InputSystem::update() {
    backend_->update();

    for (auto& [id, context] : devices_) 
    {
        RawDeviceState rawState;
        if (backend_->getRawState(id, rawState)) 
        {
            context.rawState = rawState;
            context.gamepadState = context.mapper.mapToGamepad(rawState);
        }
    }
}


const GamepadState* InputSystem::getGamepadState(DeviceId id) const {
    auto it = devices_.find(id);
    if (it == devices_.end()) {
        return nullptr;
    }
    return &it->second.gamepadState;
}

std::vector<DeviceId> InputSystem::getConnectedGamepads() const {
    std::vector<DeviceId> connected;
    for (const auto& [id, context] : devices_) {
        if (context.info.type == DeviceType::GameController) {
            connected.push_back(id);
        }
    }
    return connected;
}