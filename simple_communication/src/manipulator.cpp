#include "ros/ros.h"
#include "std_msgs/Int16.h"

void chatterCallback(const std_msgs::Int16::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d]", (msg->data)*(msg->data));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "manipulator");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/task1/numbers", 1000, chatterCallback);

  ros::spin();

  return 0;
}
