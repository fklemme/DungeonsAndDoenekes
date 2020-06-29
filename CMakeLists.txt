cmake_minimum_required(VERSION 3.11)

# Program name
project(DungeonsAndDoenekes)

# Define target
add_executable(${PROJECT_NAME})

# Set C++ standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Add sources and include directory
file(GLOB_RECURSE hdr "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hpp")
file(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_sources(${PROJECT_NAME} PRIVATE ${hdr} PRIVATE ${src})
# For Visual Studio filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/inc PREFIX "Header Files" FILES ${hdr})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${src})

# Enable more warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Add SFML
if(WIN32)
    set(BUILD_SHARED_LIBS FALSE)
endif()
add_subdirectory(ext/SFML)
# (link_libraries for sfml-graphics, sfml-system and sfml-window are included in "ImGui-SFML" below)

# ImGui for SFML
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/imgui)
add_subdirectory(ext/imgui-sfml)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML)

# Copy game resources to build directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})