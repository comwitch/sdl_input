#include "InputSystem.h"
#include "InputTypes.h"
#include "Mapper.h"
#include "SDLInputBackend.h"

#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace {

InputSystem make_sdl_input_system() {
    return InputSystem(std::make_unique<SDLInputBackend>());
}

}  // namespace

PYBIND11_MODULE(sdl_input, m) {
    m.doc() = "SDL gamepad input bindings";

    py::enum_<DeviceType>(m, "DeviceType")
        .value("Unknown", DeviceType::Unknown)
        .value("Joystick", DeviceType::Joystick)
        .value("GameController", DeviceType::GameController);

    py::enum_<GamepadAxis>(m, "GamepadAxis")
        .value("LeftStickX", GamepadAxis::LeftStickX)
        .value("LeftStickY", GamepadAxis::LeftStickY)
        .value("RightStickX", GamepadAxis::RightStickX)
        .value("RightStickY", GamepadAxis::RightStickY)
        .value("LeftTrigger", GamepadAxis::LeftTrigger)
        .value("RightTrigger", GamepadAxis::RightTrigger);

    py::enum_<GamepadButton>(m, "GamepadButton")
        .value("South", GamepadButton::South)
        .value("East", GamepadButton::East)
        .value("West", GamepadButton::West)
        .value("North", GamepadButton::North)
        .value("LeftShoulder", GamepadButton::LeftShoulder)
        .value("RightShoulder", GamepadButton::RightShoulder)
        .value("Back", GamepadButton::Back)
        .value("Start", GamepadButton::Start)
        .value("LeftStick", GamepadButton::LeftStick)
        .value("RightStick", GamepadButton::RightStick)
        .value("DpadUp", GamepadButton::DpadUp)
        .value("DpadDown", GamepadButton::DpadDown)
        .value("DpadLeft", GamepadButton::DpadLeft)
        .value("DpadRight", GamepadButton::DpadRight);

    py::class_<InputDeviceInfo>(m, "InputDeviceInfo")
        .def_readonly("id", &InputDeviceInfo::id)
        .def_readonly("name", &InputDeviceInfo::name)
        .def_readonly("type", &InputDeviceInfo::type)
        .def_readonly("guid", &InputDeviceInfo::guid)
        .def_readonly("axis_count", &InputDeviceInfo::axisCount)
        .def_readonly("button_count", &InputDeviceInfo::buttonCount)
        .def_readonly("hat_count", &InputDeviceInfo::hatCount);

    py::class_<RawDeviceState>(m, "RawDeviceState")
        .def(py::init<>())
        .def_readwrite("axes", &RawDeviceState::axes)
        .def_readwrite("buttons", &RawDeviceState::buttons)
        .def_readwrite("hats", &RawDeviceState::hats);

    py::class_<GamepadState>(m, "GamepadState")
        .def(py::init<>())
        .def_readonly("left_stick_x", &GamepadState::leftStickX)
        .def_readonly("left_stick_y", &GamepadState::leftStickY)
        .def_readonly("right_stick_x", &GamepadState::rightStickX)
        .def_readonly("right_stick_y", &GamepadState::rightStickY)
        .def_readonly("left_trigger", &GamepadState::leftTrigger)
        .def_readonly("right_trigger", &GamepadState::rightTrigger)
        .def_readonly("south", &GamepadState::south)
        .def_readonly("east", &GamepadState::east)
        .def_readonly("west", &GamepadState::west)
        .def_readonly("north", &GamepadState::north)
        .def_readonly("left_shoulder", &GamepadState::leftShoulder)
        .def_readonly("right_shoulder", &GamepadState::rightShoulder)
        .def_readonly("back", &GamepadState::back)
        .def_readonly("start", &GamepadState::start)
        .def_readonly("left_stick", &GamepadState::leftStick)
        .def_readonly("right_stick", &GamepadState::rightStick)
        .def_readonly("dpad_up", &GamepadState::dpadUp)
        .def_readonly("dpad_down", &GamepadState::dpadDown)
        .def_readonly("dpad_left", &GamepadState::dpadLeft)
        .def_readonly("dpad_right", &GamepadState::dpadRight);

    py::class_<AxisMapping>(m, "AxisMapping")
        .def(py::init<>())
        .def_readwrite("raw_axis", &AxisMapping::rawAxis)
        .def_readwrite("deadzone", &AxisMapping::deadzone)
        .def_readwrite("invert", &AxisMapping::invert);

    py::class_<ButtonMapping>(m, "ButtonMapping")
        .def(py::init<>())
        .def_readwrite("raw_button", &ButtonMapping::rawButton);

    py::class_<HatMapping>(m, "HatMapping")
        .def(py::init<>())
        .def_readwrite("raw_hat", &HatMapping::rawHat)
        .def_readwrite("mask", &HatMapping::mask);

    py::class_<DeviceMapper>(m, "DeviceMapper")
        .def(py::init<>())
        .def("set_sdl_default_mapping", &DeviceMapper::setSDLDefaultMapping)
        .def("map_to_gamepad", &DeviceMapper::mapToGamepad)
        .def_readwrite("left_stick_x", &DeviceMapper::leftStickX)
        .def_readwrite("left_stick_y", &DeviceMapper::leftStickY)
        .def_readwrite("right_stick_x", &DeviceMapper::rightStickX)
        .def_readwrite("right_stick_y", &DeviceMapper::rightStickY)
        .def_readwrite("left_trigger", &DeviceMapper::leftTrigger)
        .def_readwrite("right_trigger", &DeviceMapper::rightTrigger)
        .def_readwrite("south", &DeviceMapper::south)
        .def_readwrite("east", &DeviceMapper::east)
        .def_readwrite("west", &DeviceMapper::west)
        .def_readwrite("north", &DeviceMapper::north)
        .def_readwrite("left_shoulder", &DeviceMapper::leftShoulder)
        .def_readwrite("right_shoulder", &DeviceMapper::rightShoulder)
        .def_readwrite("back", &DeviceMapper::back)
        .def_readwrite("start", &DeviceMapper::start)
        .def_readwrite("left_stick", &DeviceMapper::leftStick)
        .def_readwrite("right_stick", &DeviceMapper::rightStick)
        .def_readwrite("dpad_up", &DeviceMapper::dpadUp)
        .def_readwrite("dpad_down", &DeviceMapper::dpadDown)
        .def_readwrite("dpad_left", &DeviceMapper::dpadLeft)
        .def_readwrite("dpad_right", &DeviceMapper::dpadRight);

    py::class_<InputSystem>(m, "InputSystem")
        .def(py::init(&make_sdl_input_system))
        .def("initialize", &InputSystem::initialize)
        .def("update", &InputSystem::update)
        .def("get_connected_gamepads", &InputSystem::getConnectedGamepads)
        .def("get_gamepad_state", [](const InputSystem& self, DeviceId id) -> py::object {
            const GamepadState* state = self.getGamepadState(id);
            if (!state) {
                return py::none();
            }
            return py::cast(*state);
        });
}
