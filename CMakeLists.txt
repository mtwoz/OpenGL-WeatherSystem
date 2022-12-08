cmake_minimum_required(VERSION 3.23)
project(weather)
set(CMAKE_CXX_STANDARD 14)

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})

# test
add_executable(test test.cpp)
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# example
add_executable(example example/example.cpp)
target_link_libraries(example ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# Road
add_executable(jumproad Road/main.cpp)
target_link_libraries(jumproad ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# Assessment 2
file(GLOB srcfiles "*.cpp" "*/*.cpp")
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/Road/main.cpp)
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp)
add_executable(weather ${srcfiles})
target_link_libraries(weather ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)
include_directories(${PROJECT_SOURCE_DIR}/utilities)
include_directories(${PROJECT_SOURCE_DIR}/snow)
include_directories(${PROJECT_SOURCE_DIR}/camera)