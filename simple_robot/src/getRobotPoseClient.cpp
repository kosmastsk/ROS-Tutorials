#include <ros/ros.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <simple_robot_msgs/GetRobotPoseAction.h>
#include <simple_robot_msgs/VictimFound.h>

class clientPub
{
private:
ros::Subscriber sub;
ros::NodeHandle n;

public:
clientPub(){
        sub = n.subscribe("/data_fusion/victim_found", 1000, &clientPub::victimFoundCallback, this);
}

void victimFoundCallback(const simple_robot_msgs::VictimFound::ConstPtr& msg)
{
        //ROS_INFO("I heard: [%s]", msg->sensor.c_str());

        getActionResultAndPrint(msg->sensor);
}

void getActionResultAndPrint(std::string sensor_type){
        // create the action client
        // true causes the client to spin its own thread
        actionlib::SimpleActionClient<simple_robot_msgs::GetRobotPoseAction> ac("/slam/get_robot_pose", true);

        ROS_INFO("Waiting for action server to start.");
        // wait for the action server to start
        ac.waitForServer(); //will wait for infinite time

        ROS_INFO("Action server started");

        simple_robot_msgs::GetRobotPoseGoal goal;
        goal.empty_goal = 0;
        ac.sendGoal(goal);

        //wait for the action to return
        bool finished_before_timeout = ac.waitForResult(ros::Duration(200.0));

        if (finished_before_timeout)
        {
                //actionlib::SimpleClientGoalState state = ac.getState();
                //Kapws prepei na parw to result x kai y
                simple_robot_msgs::GetRobotPoseResult result = *ac.getResult();

                ROS_INFO("Victim found! Robot pose = (%d, %d). Sensor used for identification = %s", result.x, result.y, sensor_type.c_str());
        }
        else{
                ROS_INFO("Action did not finish before the time out.");
        }
}

};


int main(int argc, char **argv)
{
        ros::init(argc, argv, "getRobotPoseClient");

        clientPub object;

        ros::spin();

        return 0;
}
