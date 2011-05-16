#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description: Arduino CMake example                                          #
#                                                                             #
#=============================================================================#
set(CMAKE_MODULE_PATH    ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchains/Arduino.cmake)


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(DHT C CXX)
find_package(Arduino 22 REQUIRED)

include_directories(lib)
add_subdirectory(lib/dht)
add_subdirectory(src)
