cmake_minimum_required(VERSION 2.8.8)
project(SOKOBAN)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include_directories(
  ${GLEW_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${SDL_INCLUDE_DIR}
  )

add_executable(
  sokoban
  main.cpp
  )

target_link_libraries(
  sokoban
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${SDL_LIBRARY}
  )
