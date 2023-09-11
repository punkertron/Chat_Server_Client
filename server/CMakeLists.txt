project(Server VERSION 1.0 LANGUAGES CXX)
include(../common.cmake)

add_executable(server ${SOURCES})

target_compile_options(server PRIVATE
    -Wall
    -Wextra
    -O2
)

target_link_libraries(server Boost::system)