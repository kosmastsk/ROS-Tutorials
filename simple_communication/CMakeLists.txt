cmake_minimum_required(VERSION 2.8.3)
project(simple_communication)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rostime
  std_msgs
)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
#generate_messages(DEPENDENCIES std_msgs)

## The catkin_package macro generates cmake config files for your package
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(streamer src/streamer.cpp)
target_link_libraries(streamer ${catkin_LIBRARIES})
add_dependencies(streamer simple_communication_generate_messages_cpp)

add_executable(manipulator src/manipulator.cpp)
target_link_libraries(manipulator ${catkin_LIBRARIES})
add_dependencies(manipulator simple_communication_generate_messages_cpp)