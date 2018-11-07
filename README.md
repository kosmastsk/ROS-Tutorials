# ROS Tutorials

Implementation of the ROS tutorials provided by [R4A WiKi](https://kastor.ee.auth.gr/)  
These tasks contain the following:
* ROS Publisher and Subscriber   :point_right:   /simple_communication
* Tic Tac Toe implementation using:
    * ROS Services   :point_right:   /complex_communication
    * ROS Actions   :point_right:   /complex_communication_actions
* Multiple node project   :point_right:    	/simple_robot,  	/simple_robot_msgs
* ROS Publisher and Subscriber using static and dynamic parameters   :point_right:    	/simple_communication_dynamic
* [tf](http://wiki.ros.org/tf/Tutorials/Introduction%20to%20tf)   :point_right:    	/learning_tf
* [CRSM SLAM](https://github.com/etsardou/crsm-slam-ros-pkg)   :point_right:   /crsm-slam-ros-pkg
* [MCL algorithm (Monte Carlo Localization)](https://github.com/robotics-4-all/r4a_MCL)   :point_right:    	/r4a_MCL
* Obstacle avoidance and CRSM SLAM using STDR Simulator   :point_right:    	/obstacle_avoidance
* Obstacle avoidance and CRSM SLAM using Gazebo Simulator   :point_right:    	 	/gazebo_obstacle_avoidance

### Prerequisites

Ubuntu 16.04  
ROS Kinetic

Depending on the task, you may need the following packages installed:
* [Rviz](http://wiki.ros.org/rviz)
* [STDR](http://stdr-simulator-ros-pkg.github.io/)
* [Gazebo](http://wiki.ros.org/gazebo_ros_pkgs)

### Running the demos

Each folder contains a different launch file that runs a different task. So in order to run a demo, for example *Obstacle Avoidance* package using keyboard, change directory to your catkin workspace and type:

```
$ catkin build obstacle avoidance
$ source devel/setup.bash
$ roslaunch obstacle_avoidance stdr_keyboard.launch
```
Beware! Sometimes you may need to change some configuration parameters to combine the packages between them.
