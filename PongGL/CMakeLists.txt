#http://derekmolloy.ie/hello-world-introductions-to-cmake/

#specify minimum make version
cmake_minimum_required(VERSION 3.10.2)

#specify project name
project (PongGL)

#c++11
set(CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED STATIC)

#find GLFW
pkg_search_module(GLFW REQUIRED glfw3)
find_package (glfw3 REQUIRED)

#find GLM
pkg_search_module(GLM REQUIRED glm)
find_package (glm REQUIRED)

#Bring the headers into the project
include_directories(
    ${GLM_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    include/pongGL/
    include/pongGL/entity
    include/pongGL/entity/component
    include/pongGL/entity/component/ai
    include/pongGL/entity/component/graphics
    include/pongGL/entity/component/physics
    include/pongGL/entity/component/input
    include/pongGL/graphics
    include/pongGL/physics)

#Specify the source files using the file(GLOB...) wildcard:
file(GLOB_RECURSE SOURCES "*.cpp")

#MESSAGE(STATUS "glfw3 = ${glfw3}")

#build executable
add_executable(pongGL ${SOURCES})
target_link_libraries (pongGL
                        ${OPENGL_LIBRARIES}
                        ${GLFW_LIBRARIES}
                        ${GLEW_LIBRARY})
