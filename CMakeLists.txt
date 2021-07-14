cmake_minimum_required(VERSION 3.19)
project(ssp_controller)

set(CMAKE_CXX_STANDARD 14)

add_executable(ssp_controller main.cpp Plant.cpp Plant.h Controller.cpp Controller.h Prescient.cpp Prescient.h)