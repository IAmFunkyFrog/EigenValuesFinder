cmake_minimum_required(VERSION 3.17)
project(EigenValuesFinder)

set(CMAKE_CXX_STANDARD 14)

add_executable(EigenValuesFinder main.cpp libs/InputParser/InputParser.h libs/RationalNum/RationalNum.h libs/RationalNum/RationalNum.cpp libs/InputParser/InputParser.cpp libs/MatrixUtils/MatrixUtils.h libs/MatrixUtils/MatrixUtils.cpp)