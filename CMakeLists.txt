cmake_minimum_required(VERSION 3.12)
project(TP2)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP2 testGrayLevelImage2D.cpp Image2D.hpp Color.hpp testColorImage2D.cpp Image2DWriter.hpp)