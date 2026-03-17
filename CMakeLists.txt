cmake_minimum_required(VERSION 3.16)

project(sdl_input VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

add_library(sdl_input_backend STATIC
    src/SDLInputBackend.cpp
)

target_include_directories(sdl_input_backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(sdl_input_backend
    PUBLIC
        SDL2::SDL2
)

add_executable(device_checker
    src/device_checker.cpp
)

target_include_directories(device_checker
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(device_checker
    PRIVATE
        SDL2::SDL2
)
