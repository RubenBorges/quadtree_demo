set(SOURCES
    SFML.cpp
    quadtree.cpp
    ZenityDialog.cpp 
    )

set(HEADERS
    include/quadtree.h
    include/ZenityDialog.hpp
    )
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(QuadTreeDemo ${SOURCES} ${HEADERS})

target_link_libraries(QuadTreeDemo PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_include_directories(QuadTreeDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(QuadTreeDemo PRIVATE -O2 -Wall -Wextra)

install(TARGETS QuadTreeDemo DESTINATION bin)
