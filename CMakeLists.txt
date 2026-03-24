cmake_minimum_required(VERSION 3.16)
project(InputSystemTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(InputSystemTest
    src/main.cpp
    include/InputSystem.cpp
    include/Mapper.cpp
    include/SDLInputBackend.cpp
)

target_include_directories(InputSystemTest PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(InputSystemTest PRIVATE SDL2::SDL2)