cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME "openGLTutorial")
set(CMAKE_CXX_STANDARD 20)
set(SHADER_DIR ${CMAKE_BINARY_DIR}/src/shaders)

project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

if(EXISTS ${CMAKE_BINARY_DIR}/conanBuild/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanBuild/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run ./build.sh first")
endif()

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RES_FILES} main.cpp)

# Copy src/resources -> bin/resources
file(COPY ${CMAKE_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
