project(Client VERSION 1.0 LANGUAGES CXX)
include(../common.cmake)

add_executable(client ${SOURCES})

target_compile_options(client PRIVATE
    -Wall
    -Wextra
    -O2
)
target_compile_features(client PRIVATE cxx_std_17)
target_link_libraries(client Boost::system ChatMessage)