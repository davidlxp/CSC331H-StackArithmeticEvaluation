cmake_minimum_required(VERSION 3.20)
project(StackArithmeticEvaluation)

set(CMAKE_CXX_STANDARD 14)

add_executable(StackArithmeticEvaluation main.cpp Stack.cpp Stack.h Node.h ArithmeticEvaluation.cpp ArithmeticEvaluation.h)
