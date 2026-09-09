cmake_minimum_required(VERSION 3.22)

project(GreenCircle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML-3.0.2"
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(green_circle main.cpp)

target_link_libraries(green_circle PRIVATE SFML::Graphics)