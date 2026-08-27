# 1. Define source files using simple relative paths
set(SOURCES
    QuadTreeDemo.cpp
    CameraController.cpp
    draw.cpp
    quadtree.cpp
    ZenityDialog.cpp 
)

# 2. Define header files (Optional: helps IDE visibility)
set(HEADERPATHS
    include/CameraController.hpp
    include/Config.hpp
    include/draw.hpp
    include/quadtree.hpp
    include/ZenityDialog.hpp
)
add_executable(QuadTreeDemo 
    ${SOURCES}
    ${HEADERPATHS}
    )

# 3. Find dependencies
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(QuadTreeDemo PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Configure compiler include search paths
target_include_directories(QuadTreeDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Apply warning and optimization flags
target_compile_options(QuadTreeDemo PRIVATE -O2 -Wall -Wextra)

