cmake_minimum_required(VERSION 3.17)
project(ToyScheduler)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_LIB src/Task.h src/SolutionBase.h src/KnapsackSolver.h src/KnapsackSolution.h src/GreedySolution.h src/KnapsackSolver.cpp src/KnapsackSolution.cpp src/GreedySolution.cpp)
add_library(scheduler STATIC ${SOURCE_LIB})
set_target_properties(scheduler PROPERTIES LINKER_LANGUAGE CXX)

set(TEST_LIB test/TestGenerator.cpp test/TestGenerator.h test/ResultChecker.h test/ResultChecker.cpp)
add_library(test STATIC ${TEST_LIB})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)

add_executable(toyScheduler run_benchmark.cpp)

target_link_libraries(toyScheduler scheduler)
target_link_libraries(toyScheduler test)