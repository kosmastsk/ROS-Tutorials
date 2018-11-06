# ROS Tutorials

Implementation of the ROS tutorials provided by [R4A WiKi](https://kastor.ee.auth.gr/)
These tasks contain the following:
* ROS Publisher and Subscriber
* ROS Services
* ROS Actions
* Multiple node project
* ROS static and dynamic parameters
* STDR Simulator
* tf
* RViz
* [CRSM SLAM](https://github.com/etsardou/crsm-slam-ros-pkg)
* [MCL algorithm (Monte Carlo Localization)](https://github.com/robotics-4-all/r4a_MCL)

### Prerequisites

Ubuntu 16.04
ROS Kinetic

### Running the demos

Each folder contains a different launch file that runs a different task. So in order to run a demo, for example *Obstacle Avoidance* package using keyboard, change directory to your catkin workspace and type:

```
catkin build obstacle avoidance
```
```
source devel/setup.bash
```
```
roslaunch obstacle_avoidance stdr_keyboard.launch
```
