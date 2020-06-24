cmake_minimum_required(VERSION 3.10)

# Program name
project(DungeonsAndDoenekes)

# Define a 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
# (Do not set C++ standard globally as SFML 2.5 is still using std::auto_ptr which has been removed in C++17)

# Enable more warnings (compare https://cmake.org/cmake/help/latest/command/add_compile_options.html)
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Add sources
file(GLOB src "src/*.h" "src/*.cpp")
add_executable(${PROJECT_NAME} ${src})

# Add SFML
if(WIN32)
    set(BUILD_SHARED_LIBS FALSE)
endif()
add_subdirectory(ext/SFML)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
