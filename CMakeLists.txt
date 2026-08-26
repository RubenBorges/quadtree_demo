cmake_minimum_required(VERSION 3.16)
project(QuadTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/cmake/SFML" CACHE PATH "SFML CMake package directory")
endif()

add_subdirectory(src)


# find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# set(SOURCES
#     SFML.cpp
#     quadtree.cpp
#     quadtree.h
#     ZenityDialog.cpp 
#     ZenityDialog.hpp
# )

# add_executable(QuadTreeDemo ${SOURCES})


# target_link_libraries(QuadTreeDemo PRIVATE
#     SFML::Graphics
#     SFML::Window
#     SFML::System
# )

# target_compile_options(QuadTreeDemo PRIVATE -O2 -Wall -Wextra)

# install(TARGETS QuadTreeDemo DESTINATION bin)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
