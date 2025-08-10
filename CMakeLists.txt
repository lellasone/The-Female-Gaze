cmake_minimum_required(VERSION 3.10)

project(the_female_gaze CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an exacutable
add_executable(the_female_gaze src/main.cpp)

# Find / Link libraries. 
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(the_female_gaze sfml-graphics sfml-window sfml-system)

# Set the include directories for the project, here we will only use the root. 
target_include_directories(the_female_gaze PRIVATE ${PROJECT_SOURCE_DIR})

#TODO: Add a configure_file section to move over fonts and images. 


