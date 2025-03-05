cmake_minimum_required(VERSION 3.10)

get_filename_component(FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${FILE_NAME})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake-helper/cmake-helper.cmake)
include_directories(${CMAKE_SOURCE_DIR}/Crow/include)
include_directories(${CMAKE_SOURCE_DIR}/asio/asio/include)

use_qt5()

add_subdirectory(src)

