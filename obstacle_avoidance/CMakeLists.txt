cmake_minimum_required(VERSION 2.8.3)
project(obstacle_avoidance)

find_package(catkin REQUIRED COMPONENTS
  roslib
  roscpp
  tf
  stdr_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
  visualization_msgs
)

set(CMAKE_BUILD_TYPE Release)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
  CATKIN_DEPENDS
    roslib
    roscpp
    tf
    stdr_msgs
    geometry_msgs
    sensor_msgs
    nav_msgs
)

####################### Obstacle avoidance ##################################
add_executable(stdr_obstacle_avoidance
  src/obstacle_avoidance/main.cpp
  src/obstacle_avoidance/obstacle_avoidance.cpp)
add_dependencies(stdr_obstacle_avoidance ${stdr_msgs_EXPORTED_TARGETS}) # wait for stdr_msgs to be build
target_link_libraries(stdr_obstacle_avoidance
  ${catkin_LIBRARIES}
)

add_executable(robot_pose_listener src/obstacle_avoidance/listener.cpp)
target_link_libraries(robot_pose_listener ${catkin_LIBRARIES})

add_executable(bounding_box src/obstacle_avoidance/boundingBox.cpp)
target_link_libraries(bounding_box ${catkin_LIBRARIES})

# Install excecutables
install(TARGETS stdr_obstacle_avoidance
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
