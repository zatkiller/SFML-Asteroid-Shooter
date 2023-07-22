cmake_minimum_required(VERSION 3.23)
project(sfml-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Find SFML shared libraries
find_package(SFML 2.6 COMPONENTS 
    system window graphics network audio REQUIRED PATHS ${SFML_SRC_PATH})

include_directories(src)

file(GLOB_RECURSE srcs src/*.cpp src/*.h)

# Compile executable
add_executable(prog ${srcs})

# Link executable to required SFML libraries
target_link_libraries(prog sfml-graphics) 
