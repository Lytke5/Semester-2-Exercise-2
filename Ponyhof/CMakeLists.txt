cmake_minimum_required(VERSION 3.5)

project(Ponyhof LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Ponyhof main.cpp pony.h pony.cpp position.h position.cpp shetlandpony.h shetlandpony.cpp
islandpferd.h islandpferd.cpp stall.h stall.cpp ponyhof.h ponyhof.cpp)

install(TARGETS Ponyhof
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
