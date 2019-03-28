cmake_minimum_required(VERSION 3.12)
project(gameproject)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)

add_executable(gameproject main.cpp ClassesOfUnits.h ClassesOfUnits.cpp Builder.h Builder.cpp Tests/TestClassWarriorWithFraction.cpp Tests/BuilderTest.cpp Tests/TestClassHealerWithFraction.cpp Tests/DirectorTest.cpp)

include_directories(lib/googletest-master/googletest/include)

include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(gameproject gtest_main)