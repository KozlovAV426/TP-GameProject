cmake_minimum_required(VERSION 3.9.2)
project(gameproject)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)

add_executable(gameproject main.cpp ClassesOfUnits.h ClassesOfUnits.cpp Builder.h Builder.cpp Tests/TestClassWarriorWithFraction.cpp Tests/BuilderTest.cpp Tests/TestClassHealerWithFraction.cpp Tests/DirectorTest.cpp Structure.h Structure.cpp Relationships.h Relationships.cpp Interface.h Interface.cpp Tests/StructureTests.cpp Tests/RelationshipsTest.cpp Tests/StressTests.cpp "Tests/InteractionTest(gmock).cpp")

include_directories(lib/googletest-master/googletest/include)

include_directories(lib/googletest-master/googlemock/include)

target_link_libraries(gameproject gtest_main)

target_link_libraries(gameproject gmock_main)
