cmake_minimum_required(VERSION 2.8.12)
set(PROJECT_NAME "sokoban")
project(${PROJECT_NAME} C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g -Wall")

set(ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets")
set(DEST_DIR "${PROJECT_SOURCE_DIR}/dest")
set(EXT_DIR "${PROJECT_SOURCE_DIR}/ext")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
  message(SEND_ERROR "GLEW not found on your system")
endif()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
  message(SEND_ERROR "OpenGL not found on your system")
endif()

find_package(PNG REQUIRED)
if(NOT PNG_FOUND)
  message(SEND_ERROR "libpng not found on your system")
endif()

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
  ${GLEW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  ${SRC_DIR}
  )

set(
  SOKOBAN_SOURCES
  ${SRC_DIR}/game.cpp
  ${SRC_DIR}/gui.cpp
  ${SRC_DIR}/helpers.cpp
  ${SRC_DIR}/menu.cpp
  ${SRC_DIR}/soko_board.cpp
  ${SRC_DIR}/soko_character.hpp
  ${SRC_DIR}/soko_object.cpp
  ${SRC_DIR}/soko_position.cpp
  )

add_library(
  SOKOBAN_LIBRARY
  OBJECT
  ${SOKOBAN_SOURCES}
  )

add_executable(
  ${PROJECT_NAME}
  ${SRC_DIR}/main.cpp
  $<TARGET_OBJECTS:SOKOBAN_LIBRARY>
  )

target_link_libraries(
  ${PROJECT_NAME}
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${PNG_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  -lSOIL
  )

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${DEST_DIR}
  )

install(
  DIRECTORY ${ASSETS_DIR}
  DESTINATION ${DEST_DIR}
  )

file(GLOB ASSETS ${ASSETS_DIR}/*)
foreach(asset ${ASSETS}) 
  file(
    COPY ${asset} 
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets
    )
endforeach(asset)

option(TEST "Build all tests." OFF)
if (TEST)
  enable_testing()
  set(PROJECT_TEST_NAME "${PROJECT_NAME}UnitTests")
  file(GLOB TEST_SRC_FILES ${TEST_DIR}/*Test.cpp)
  add_subdirectory(${EXT_DIR}/gtest)
  include_directories(${GTEST_INCLUDE_DIRS})
  add_executable(
    ${PROJECT_TEST_NAME}
    ${TEST_SRC_FILES}
    $<TARGET_OBJECTS:SOKOBAN_LIBRARY>
    )
  add_dependencies(${PROJECT_TEST_NAME} googletest)
  target_link_libraries(
    ${PROJECT_TEST_NAME}
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    -lSOIL
    pthread
    )
  GTEST_ADD_TESTS(${PROJECT_TEST_NAME} "" ${TEST_SRC_FILES})
endif()
