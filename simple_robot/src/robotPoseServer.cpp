#include <ros/ros.h>

#include <simple_robot_msgs/GetRobotPoseAction.h>  // Note: "Action" is appended
#include <actionlib/server/simple_action_server.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class GetRobotPoseAction
{
protected:
ros::NodeHandle n;
actionlib::SimpleActionServer<simple_robot_msgs::GetRobotPoseAction> Server;

std::string get_robot_pose_action_;

simple_robot_msgs::GetRobotPoseResult result_;

public:

GetRobotPoseAction(std::string name) :
        Server(n, name, boost::bind(&GetRobotPoseAction::executeCB, this, _1), false), get_robot_pose_action_(name)
{
        Server.start();
}

~GetRobotPoseAction(void)
{
}

void executeCB (const simple_robot_msgs::GetRobotPoseGoalConstPtr& goal)
{
        srand (time(NULL));

        result_.x = rand() % 9;
        result_.y = rand() % 9;

        Server.setSucceeded(result_);
}
};

int main (int argc, char** argv)
{
        ros::init(argc, argv, "robotPoseServer");

        GetRobotPoseAction server("/slam/get_robot_pose");

        ros::spin();

        return 0;
}
