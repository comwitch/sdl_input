cmake_minimum_required(VERSION 3.16)
project(InputSystemTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

set(INPUT_SYSTEM_SOURCES
    include/InputSystem.cpp
    include/Mapper.cpp
    include/SDLInputBackend.cpp
)

add_library(input_system STATIC ${INPUT_SYSTEM_SOURCES})
set_target_properties(input_system PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(input_system PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(input_system PUBLIC SDL2::SDL2)

add_executable(InputSystemTest
    src/main.cpp
)

target_include_directories(InputSystemTest PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(InputSystemTest PRIVATE input_system)

option(BUILD_PYTHON_BINDINGS "Build the pybind11 Python module" OFF)

if(BUILD_PYTHON_BINDINGS)
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
    find_package(pybind11 CONFIG REQUIRED)

    pybind11_add_module(sdl_input
        src/python_bindings.cpp
    )

    target_link_libraries(sdl_input PRIVATE input_system)
endif()
