#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <complex_communication_actions/tictactoeAction.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main (int argc, char **argv)
{
        srand (time(NULL));

        ros::init(argc, argv, "player_1");

        // create the action client
        // true causes the client to spin its own thread
        actionlib::SimpleActionClient<complex_communication_actions::tictactoeAction> ac("tictactoe", true);

        ROS_INFO("Waiting for action server to start.");
        // wait for the action server to start
        ac.waitForServer(); //will wait for infinite time

        ROS_INFO("Action server started, sending goal.");
        while (ros::ok()) {
                // send a goal to the action
                complex_communication_actions::tictactoeGoal goal;
                complex_communication_actions::tictactoeFeedback feedback_;
                goal.move = rand() % 9; // Send a random number as the next move of the player
                goal.player = 1;
                ac.sendGoal(goal);

                //wait for the action to return
                bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

                if (finished_before_timeout)
                {
                        actionlib::SimpleClientGoalState state = ac.getState();
                        ROS_INFO("Action finished: %s",state.toString().c_str());
                }
                else
                        ROS_INFO("Action did not finish before the time out.");
        }
        //exit
        return 0;
}
