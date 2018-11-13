cmake_minimum_required(VERSION 3.12)
project(TP2)

set(CMAKE_CXX_STANDARD 14)

#add_executable(TP2 testGrayLevelImage2D.cpp Image2D.hpp Color.hpp Image2DWriter.hpp Image2DReader.hpp)
#add_executable(TP2 testColorImage2D.cpp Image2D.hpp Color.hpp Image2DWriter.hpp Image2DReader.hpp)
add_executable(TP2  invert-red-blue.cpp Image2D.hpp Color.hpp Image2DWriter.hpp Image2DReader.hpp)