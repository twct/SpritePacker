cmake_minimum_required (VERSION 3.16)

project (SpritePacker)

find_package (PkgConfig)
pkg_check_modules (GTKMM gtkmm-3.0)

include_directories (
    ${CMAKE_SOURCE_DIR}/include
    ${GTKMM_INCLUDE_DIRS}
)

add_executable (${PROJECT_NAME}
    src/main.cpp
    src/SpriteGrid.cpp
    src/SpritePackerWindow.cpp
)

target_link_libraries (${PROJECT_NAME}
    ${GTKMM_LIBRARIES}
)