#pragma once

#include "InputTypes.h"

class DeviceMapper{
public:
    GamepadState mapToGamepad(const RawDeviceState& raw) const;

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

    HatMapping dpadUp;
    HatMapping dpadDown;
    HatMapping dpadLeft;
    HatMapping dpadRight;
};