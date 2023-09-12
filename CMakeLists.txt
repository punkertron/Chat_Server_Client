cmake_minimum_required(VERSION 3.25.1)
project(ChatServerClient VERSION 1.0 LANGUAGES CXX)

add_library(ChatMessage message/ChatMessage.cpp)
target_compile_options(ChatMessage PRIVATE
    -Wall
    -Wextra
    -O2
)
target_include_directories(ChatMessage PUBLIC message/)
target_compile_features(ChatMessage PRIVATE cxx_std_17)

add_subdirectory(server)
add_subdirectory(client)