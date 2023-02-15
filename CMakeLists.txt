cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME "openGLTutorial")
set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})

if(EXISTS ${CMAKE_BINARY_DIR}/conanBuild/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanBuild/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
