cmake_minimum_required(VERSION 3.10)
project(bengImage)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Locate OpenCV
find_package(OpenCV REQUIRED)
include_directories(bengImage ${OPENCV_INCLUDE_DIRS})

# standard compiler warnings
# Set compiler-specific warning flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC
    target_compile_options(bengImage PRIVATE -Wall -Wextra -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang
    target_compile_options(bengImage PRIVATE -Wall -Wextra -pedantic)
endif()

# Compile the package
add_executable(bendImage main.cpp)
target_include_directories(bendImage PRIVATE main.cpp)
target_link_libraries(bendImage ${OpenCV_LIBS})