cmake_minimum_required(VERSION 3.8)
project(Rooms)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Room.cpp Room.h Handler.cpp Handler.h Helpers.cpp Helpers.h)
add_executable(Rooms ${SOURCE_FILES})