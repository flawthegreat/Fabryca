cmake_minimum_required(VERSION 3.10)
project(Fabryca)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Fabryca_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

if(NOT DEFINED RESOURCES_DIR)
    set(RESOURCES_DIR /usr/share)
endif()

if(NOT DEFINED LAUNCHER_DIR)
    set(LAUNCHER_DIR ~/Desktop)
endif()

if(DEFINED BINARY_DIR)
    set(CMAKE_INSTALL_PREFIX ${BINARY_DIR})
endif()

find_package(glm REQUIRED)
if(NOT glm_FOUND)
    message(SEND_ERROR "Failed to find GLM library")
    return()
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(JSONCPP REQUIRED jsoncpp)

link_directories(${JSONCPP_LIBRARY_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

pkg_search_module(GLFW REQUIRED glfw3)

link_directories(${GLFW_LIBRARY_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})

include_directories(${Fabryca_SOURCE_DIR}/${CMAKE_PROJECT_NAME})

set(PROJECT_DIR ${CMAKE_PROJECT_NAME})

set(
    SOURCE_FILES 

    ${PROJECT_DIR}/utility/Point.cpp 
    ${PROJECT_DIR}/utility/NumericAttribute.cpp 
    ${PROJECT_DIR}/utility/Random.cpp
    ${PROJECT_DIR}/utility/JSON.cpp 
    ${PROJECT_DIR}/utility/Filepath.cpp 
    ${PROJECT_DIR}/utility/EventManager.h 

    ${PROJECT_DIR}/graphics/WindowManager.cpp
    ${PROJECT_DIR}/graphics/Renderer.cpp
    ${PROJECT_DIR}/graphics/Animation.cpp
    ${PROJECT_DIR}/graphics/Model.cpp
    ${PROJECT_DIR}/graphics/Camera.cpp
    ${PROJECT_DIR}/graphics/SceneObject.cpp
    ${PROJECT_DIR}/graphics/Mesh.cpp
    ${PROJECT_DIR}/graphics/Texture.cpp
    ${PROJECT_DIR}/graphics/Shader.cpp
    ${PROJECT_DIR}/graphics/VertexBuffer.cpp
    ${PROJECT_DIR}/graphics/Vertex.cpp
    ${PROJECT_DIR}/graphics/glad.c

    ${PROJECT_DIR}/Object.cpp
    ${PROJECT_DIR}/Configuration.cpp
    ${PROJECT_DIR}/GameInstance.cpp
    ${PROJECT_DIR}/Terrain.cpp
    ${PROJECT_DIR}/HealthIndicator.cpp
    ${PROJECT_DIR}/NumberDisplayer.cpp

    ${PROJECT_DIR}/characters/Character.cpp 
    ${PROJECT_DIR}/characters/Player.cpp 
    ${PROJECT_DIR}/characters/enemies/Enemy.cpp 
    ${PROJECT_DIR}/characters/enemies/ForestDemon.cpp 
    ${PROJECT_DIR}/characters/enemies/HoveringBeast.cpp 
    ${PROJECT_DIR}/characters/enemies/PoisonousMonster.cpp
)

execute_process(COMMAND mkdir -p ${Fabryca_SOURCE_DIR}/launcher)
execute_process(
    COMMAND python3 ${Fabryca_SOURCE_DIR}/generate_launcher.py 
        "${PROJECT_NAME}" 
        "${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}" 
        "${RESOURCES_DIR}/Fabryca/"
        "${Fabryca_SOURCE_DIR}/launcher"
)

add_executable(
    Fabryca
    ${SOURCE_FILES}
    ${PROJECT_DIR}/Application.cpp
)
target_link_libraries(
    Fabryca 
    glm 
    ${GLFW_LIBRARIES} 
    pthread
    ${JSONCPP_LIBRARIES}
    ${CMAKE_DL_LIBS}
)

install(
    DIRECTORY ${PROJECT_DIR}/resources/
    DESTINATION ${RESOURCES_DIR}/Fabryca
)

install(
    FILES ${Fabryca_SOURCE_DIR}/launcher/${PROJECT_NAME}.sh
    DESTINATION ${LAUNCHER_DIR}
)

install(
    TARGETS Fabryca
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

if (TESTING STREQUAL ON)
    enable_testing()

    find_package(GTest REQUIRED)
    if(NOT GTest_FOUND)
        message(SEND_ERROR "Failed to find GTest library")
        return()
    else()
        include_directories(${GTEST_INCLUDE_DIRS})
    endif()

    set(
        TEST_SOURCE_FILES 

        ${PROJECT_DIR}/testing/Tests.cpp 
        ${PROJECT_DIR}/testing/UtilityTest.cpp 
        ${PROJECT_DIR}/testing/GraphicsTest.cpp
        ${PROJECT_DIR}/testing/GameTest.cpp
    )

    execute_process(
        COMMAND python3 ${Fabryca_SOURCE_DIR}/generate_launcher.py 
            "${PROJECT_NAME}Tests" 
            "${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}Tests" 
            "${RESOURCES_DIR}/Fabryca/"
            "${Fabryca_SOURCE_DIR}/launcher"
    )

    install(
        FILES ${Fabryca_SOURCE_DIR}/launcher/${PROJECT_NAME}Tests.sh
        DESTINATION ${LAUNCHER_DIR}
    )

    add_executable(
        FabrycaTests
        ${SOURCE_FILES}
        ${TEST_SOURCE_FILES}
    )
    target_link_libraries(
        FabrycaTests 
        ${GTEST_BOTH_LIBRARIES} 
        pthread 
        glm 
        ${GLFW_LIBRARIES}
        ${JSONCPP_LIBRARIES}
        ${CMAKE_DL_LIBS}
    )

    install(
        TARGETS FabrycaTests
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    )
endif()