#pragma once

#include "InputTypes.h"

class DeviceMapper{
public:
    GamepadState mapToGamepad(const RawDeviceState& raw) const;

    void setSDLDefaultMapping();
    float readAxis(const RawDeviceState& raw, const AxisMapping& mapping) const;
    bool readButton(const RawDeviceState& raw, const ButtonMapping& mapping) const;

    AxisMapping leftStickX;
    AxisMapping leftStickY;
    AxisMapping rightStickX;
    AxisMapping rightStickY;
    AxisMapping leftTrigger;
    AxisMapping rightTrigger;

    ButtonMapping south;
    ButtonMapping east;
    ButtonMapping west;
    ButtonMapping north;
    ButtonMapping leftShoulder;
    ButtonMapping rightShoulder;
    ButtonMapping back;
    ButtonMapping start;
    ButtonMapping leftStick;
    ButtonMapping rightStick;

    ButtonMapping dpadUp;
    ButtonMapping dpadDown;
    ButtonMapping dpadLeft;
    ButtonMapping dpadRight;
};