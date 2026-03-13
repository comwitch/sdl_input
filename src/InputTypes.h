#pragma once

using DeviceId = uint64_t;


enum class DeviceType{
    Unknown,
    Joystick,
    Gamepad
};

enum class GamepadAxis{
    LeftStickX,
    LeftStickY,
    RightStickX,
    RightStickY,
    LeftTrigger,
    RightTrigger,
};

enum class GamepadButton{
    South,
    East,
    West,
    North,
    LeftShoulder,
    RightShoulder,
    Back,
    Start,
    LeftStick,
    RightStick,
    DpadUp,
    DpadDown,
    DpadLeft,
    DpadRight
};

struct InputDeviceInfo{
    DeviceId id;
    std::string name;
    DeviceType type=DeviceType::Unknown;
    std::string guid;
    int axisCount=0;
    int buttonCount=0;
    int hatCount=0;
};

struct RawDeviceState{
    std::vector<float> axes;
    std::vector<bool> buttons;
    std::vector<int> hats;
};

struct GamepadState{
    float leftStickX=0.0f;
    float leftStickY=0.0f;
    float rightStickX=0.0f;
    float rightStickY=0.0f;
    float leftTrigger=0.0f;
    float rightTrigger=0.0f;

    bool south=false;
    bool east=false;
    bool west=false;
    bool north=false;
    bool leftShoulder=false;
    bool rightShoulder=false;
    bool back=false;
    bool start=false;
    bool leftStick=false;
    bool rightStick=false;
    bool dpadUp=false;
    bool dpadDown=false;
    bool dpadLeft=false;
    bool dpadRight=false;
};

struct AxisMapping{
    int rawAxis=-1;
    float deadzone=0.1f;
    bool invert=false;
};

struct ButtonMapping{
    int rawButton=-1;
};

struct HatMapping{
    int rawHat=-1;
    int mask=0;
};