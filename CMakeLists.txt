cmake_minimum_required(VERSION 2.8.8)
project(SOKOBAN)

find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(
  sokoban
  main.cpp
  )

target_link_libraries(
  sokoban
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )
