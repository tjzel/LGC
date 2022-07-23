cmake_minimum_required(VERSION 3.10)

# set the project name
project(LGC VERSION 0.01)

configure_file(LGCConfig.h.in LGCConfig.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

# add the executable
add_executable(LGC ../src/main.cpp)

target_include_directories(LGC PUBLIC "${PROJECT_BINARY_DIR}")
