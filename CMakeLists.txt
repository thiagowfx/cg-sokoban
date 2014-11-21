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
find_package(OpenGL REQUIRED)
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
  ${GLEW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIRS}
  )

set(
  SOKOBAN_SOURCES
  ${SRC_DIR}/game.cpp
  ${SRC_DIR}/gui.cpp
  ${SRC_DIR}/helpers.cpp
  ${SRC_DIR}/menu.cpp
  ${SRC_DIR}/soko_board.cpp
  ${SRC_DIR}/soko_character.hpp
  ${SRC_DIR}/soko_direction.hpp
  ${SRC_DIR}/soko_object.hpp
  ${SRC_DIR}/soko_position.hpp
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
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  )

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${DEST_DIR}
  )

install(
  DIRECTORY ${ASSETS_DIR}
  DESTINATION ${DEST_DIR}
  )

file(GLOB_RECURSE ASSETS ${ASSETS_DIR}/*)
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
  add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
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
    pthread
    )
  GTEST_ADD_TESTS(${PROJECT_TEST_NAME} "" ${TEST_SRC_FILES})
endif()
