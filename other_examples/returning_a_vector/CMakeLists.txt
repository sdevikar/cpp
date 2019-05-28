project(returning_a_vector)

cmake_minimum_required(VERSION "3.13.4")

set(SOURCES
  main.cpp
  vector_populator.cpp
)

add_executable(returning_a_vector ${SOURCES})
