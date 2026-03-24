#include "Mapper.h"
#include <cmath>


// this function is mapping from RawDeviceState to GamepadState
GamepadState DeviceMapper::mapToGamepad(const RawDeviceState& raw) const {

    GamepadState state;
    state.leftStickX = readAxis(raw, leftStickX);
    state.leftStickY = readAxis(raw, leftStickY);
    state.rightStickX = readAxis(raw, rightStickX);
    state.rightStickY = readAxis(raw, rightStickY);
    state.leftTrigger = readAxis(raw, leftTrigger);
    state.rightTrigger = readAxis(raw, rightTrigger);
    state.south = readButton(raw, south);
    state.east = readButton(raw, east);
    state.west = readButton(raw, west);
    state.north = readButton(raw, north);
    state.leftShoulder = readButton(raw, leftShoulder);
    state.rightShoulder = readButton(raw, rightShoulder);
    state.back = readButton(raw, back);
    state.start = readButton(raw, start);
    state.leftStick = readButton(raw, leftStick);
    state.rightStick = readButton(raw, rightStick);
    state.dpadUp = readButton(raw, dpadUp);
    state.dpadDown = readButton(raw, dpadDown);
    state.dpadLeft = readButton(raw, dpadLeft);
    state.dpadRight = readButton(raw, dpadRight);

    return state;
}

// 이게 맞는지 잘 모르겟는데여
void DeviceMapper::setSDLDefaultMapping() {
    leftStickX = {0, 0.1f, false};
    leftStickY = {1, 0.1f, true}; // Invert Y axis
    rightStickX = {2, 0.1f, false};
    rightStickY = {3, 0.1f, true}; // Invert Y axis
    leftTrigger = {4, 0.1f, false};
    rightTrigger = {5, 0.1f, false};

    south = {0};
    east = {1};
    west = {2};
    north = {3};
    leftShoulder = {4};
    rightShoulder = {5};
    back = {6};
    start = {7};
    leftStick = {8};
    rightStick = {9};

    dpadUp = {10};
    dpadDown = {11};
    dpadLeft = {12};
    dpadRight = {13};
}

float DeviceMapper::readAxis(const RawDeviceState& raw, const AxisMapping& mapping) const {
    if (mapping.rawAxis < 0 || mapping.rawAxis >= static_cast<int>(raw.axes.size()))
        return 0.0f; // Invalid mapping
    float value = raw.axes[mapping.rawAxis] / 32768.0f; // Normalize assuming 16-bit axis input
    if (mapping.invert) value = -value;
    if (std::abs(value) < mapping.deadzone) return 0.0f; // Apply deadzone
    return value;
}

bool DeviceMapper::readButton(const RawDeviceState& raw, const ButtonMapping& mapping) const {
    if (mapping.rawButton < 0 || mapping.rawButton >= static_cast<int>(raw.buttons.size()))
        return false; // Invalid mapping
    return raw.buttons[mapping.rawButton];
}