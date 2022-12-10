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
add_executable(test example/test.cpp)
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# example
add_executable(example example/example.cpp)
target_link_libraries(example ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# Flag_demo
add_executable(flag example/Flag_demo/imageloader.cpp example/Flag_demo/IndianFlag.cpp)
target_link_libraries(flag ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)

# Assessment 2
file(GLOB srcfiles "*.cpp" "*/*.cpp")
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/Road/main.cpp)
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/example/test.cpp)
list(REMOVE_ITEM srcfiles ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp)
add_executable(weather ${srcfiles})
target_link_libraries(weather ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glut)
include_directories(${PROJECT_SOURCE_DIR}/utilities)
include_directories(${PROJECT_SOURCE_DIR}/snow)
include_directories(${PROJECT_SOURCE_DIR}/rain)
include_directories(${PROJECT_SOURCE_DIR}/flag)
include_directories(${PROJECT_SOURCE_DIR}/ground)
include_directories(${PROJECT_SOURCE_DIR}/building)
include_directories(${PROJECT_SOURCE_DIR}/camera)