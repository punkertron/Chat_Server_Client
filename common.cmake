cmake_minimum_required(VERSION 3.25.1)

find_package(Boost REQUIRED COMPONENTS system)

if(!Boost_FOUND)
    message(FATAL_ERROR "Boost not found. Please install Boost or specify its location.")
endif()

# bad practice
file(GLOB SOURCES srcs/*.cpp)

# bad practice
include_directories(incs)