cmake_minimum_required(VERSION 3.5.0)
project(splitDataForObjectDetection VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
include(CTest)
enable_testing()

add_executable(splitDataForObjectDetection main.cpp)

target_link_libraries( splitDataForObjectDetection ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)