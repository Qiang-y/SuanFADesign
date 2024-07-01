cmake_minimum_required(VERSION 3.25.1)

#set (CMAKE_C_COMPILER D:/MinGW/mingw64/bin/gcc)
#set (CMAKE_CXX_COMPILER D:/MinGW/mingw64/bin/g++)

project(COMPILE_DES)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)      #设置标准
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(out ${SRC})
