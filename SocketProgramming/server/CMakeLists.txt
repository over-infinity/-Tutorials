cmake_minimum_required(VERSION 3.5)

project(serverDemo VERSION 0.1 LANGUAGES C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/server.c)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(serverDemo ${PROJECT_SOURCES})
target_include_directories(serverDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
