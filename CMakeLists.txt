cmake_minimum_required(VERSION 3.5)
project(UBCalculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    error_handling.cpp
    error_handling.h
    Lexer.cpp
    Lexer.h
    UBCalcDriver.cpp
    UBCalculator.cpp
    UBCalculator.h)

add_executable(UBCalculator ${SOURCE_FILES})