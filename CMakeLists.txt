cmake_minimum_required(VERSION 3.11)

# Program name
project(DungeonsAndDoenekes)

# Define target
add_executable(${PROJECT_NAME})

# Set C++ standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Add sources and include directory
file(GLOB hdr "inc/*.hpp" "inc/*/*.hpp")
file(GLOB src "src/*.cpp" "src/*/*.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_sources(${PROJECT_NAME} PUBLIC ${hdr} PRIVATE ${src})


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
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

# Copy game resources to build directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})