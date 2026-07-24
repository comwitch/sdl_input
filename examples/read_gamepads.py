import time

import sdl_input


def main():
    inputs = sdl_input.InputSystem()

    while True:
        inputs.update()

        for device_id in inputs.get_connected_gamepads():
            state = inputs.get_gamepad_state(device_id)
            if state is None:
                continue

            print(
                f"id={device_id} "
                f"LX={state.left_stick_x:.3f} "
                f"LY={state.left_stick_y:.3f} "
                f"A={state.south} "
                f"B={state.east}"
            )

        time.sleep(0.1)


if __name__ == "__main__":
    main()
