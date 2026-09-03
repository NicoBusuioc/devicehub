#to compile: cmake -S . -B ./build
#to build:   cmake --build build

cmake_minimum_required(VERSION 3.22.0)
project(devicehub)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Device.cpp
    )

# private here means, that this project must be build with c++20 std, aber
# those clients, that are using it, will not, in case it will be a library
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)