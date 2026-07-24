# Joystick input system

install SDL2

## Build C++ example

```sh
cmake -S . -B build
cmake --build build
./build/InputSystemTest
```

## Build Python bindings

Install pybind11 in the Python environment you want to use:

```sh
python3 -m pip install pybind11
```

Build the extension module:

```sh
cmake -S . -B build -DBUILD_PYTHON_BINDINGS=ON -Dpybind11_DIR="$(python3 -m pybind11 --cmakedir)"
cmake --build build
```

Run the Python example:

```sh
PYTHONPATH=build python3 examples/read_gamepads.py
```

Minimal Python usage:

```python
import sdl_input

inputs = sdl_input.InputSystem()
inputs.update()

for device_id in inputs.get_connected_gamepads():
    state = inputs.get_gamepad_state(device_id)
    print(device_id, state.left_stick_x, state.south)
```
