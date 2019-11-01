cmake_minimum_required(VERSION 3.5)
project(file_test_example)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES file_pro.cpp find_file.h)
add_executable(file_test ${SOURCE_FILES})
# OpenCV libs
find_package(OpenCV REQUIRED)
include_directories("./")
include_directories(${OpenCV_INCLUDE_DIRS})
#include_directories(/usr/include/x86_64-linux-gnu/sys)
target_link_libraries(file_test ${OpenCV_LIBS})

# ==================== PATHS TO SPECIFY! ==================== #

# Eigen lib headers

# Link TensorFlow libs


