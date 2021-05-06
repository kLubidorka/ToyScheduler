cmake_minimum_required(VERSION 3.17)
project(ToyScheduler)

set(CMAKE_CXX_STANDARD 14)

add_executable(ToyScheduler main.cpp TestGenerator.cpp TestGenerator.h Task.h
        SolutionBase.h KnapsackSolver.h KnapsackSolution.h GreedySolution.h
        ResultChecker.h ResultChecker.cpp)
