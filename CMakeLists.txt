cmake_minimum_required(VERSION 3.10)
project(Fabryca)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Fabryca_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Fabryca_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

include_directories(${Fabryca_SOURCE_DIR}/Fabryca)

enable_testing()
find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message(SEND_ERROR "Failed to find GTest library")
    return()
else()
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

set(
    SOURCE_FILES 

    Fabryca/GameObject.cpp 

    Fabryca/Utility/NumericAttribute.cpp 
    Fabryca/Utility/Point.cpp 
    Fabryca/Utility/Random.cpp 

    Fabryca/Characters/Character.cpp 
    Fabryca/Characters/Human.cpp 
    Fabryca/Characters/Player.cpp 

    Fabryca/Characters/Enemies/Enemy.cpp 
    Fabryca/Characters/Enemies/ForestDemon.cpp 
    Fabryca/Characters/Enemies/HoveringBeast.cpp 
    Fabryca/Characters/Enemies/PoisonousMonster.cpp
)
set(
    TEST_SOURCE_FILES 

    Fabryca/Testing/FabrycaTests.cpp 
    Fabryca/Testing/UtilityTest.cpp 
    Fabryca/Testing/CharacterTest.cpp
)

add_executable(
    FabrycaTests
    ${SOURCE_FILES}
    ${TEST_SOURCE_FILES}
)
target_link_libraries(FabrycaTests ${GTEST_BOTH_LIBRARIES} pthread)

install(
    TARGETS FabrycaTests
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
