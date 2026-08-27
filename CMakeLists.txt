cmake_minimum_required(VERSION 3.16)
project(QuadTreeDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/cmake/SFML" CACHE PATH "SFML CMake package directory")
endif()

add_subdirectory(src)

install(TARGETS QuadTreeDemo DESTINATION bin) # Define installation rules