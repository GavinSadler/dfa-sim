
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(dfa-sim LANGUAGES CXX C)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_library(
        iotivity
        STATIC
        getopt.c
    )
    set_target_properties(iotivity PROPERTIES LINKER_LANGUAGE C)
endif()

add_library(
    dfa
    STATIC
    dfa.cpp
)

add_executable(dfa-sim main.cpp)

target_link_libraries(dfa-sim dfa)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(dfa-sim iotivity)
endif()

# Create a custom target that always runs
add_custom_target (copy-machines ALL
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-machines.cmake)

# Make the custom target depend on the main target
add_dependencies (copy-machines dfa-sim)