cmake_minimum_required(VERSION 3.0.2)
project(jslam)

add_compile_options(-std=c++11)

find_package(
        catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
)

catkin_package(
        INCLUDE_DIRS src
        CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
        ${catkin_INCLUDE_DIRS}
)

add_executable(
        jslam
        src/main.cpp
        src/gradient_solver/gradient_solver.cpp
)

target_link_libraries(jslam ${catkin_LIBRARIES})