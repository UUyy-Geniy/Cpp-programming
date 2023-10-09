cmake_minimum_required(VERSION 3.24)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator CalculatorApp.cpp Operations.cpp Operations.h Calculator.cpp Calculator.h Loader.cpp Loader.h)
