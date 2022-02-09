cmake_minimum_required(VERSION 3.15)
project(project_oracle)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_oracle main.cpp src/GameManager.cpp include/GameManager.hpp include/globals.hpp src/Button.cpp include/Button.hpp)

target_link_libraries(project_oracle raylib GL m pthread dl rt X11)

target_include_directories(project_oracle PRIVATE include/)