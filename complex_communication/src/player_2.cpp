// player_1.cpp
//System
#include <time.h> /* time */
#include <signal.h>

// ROS
#include "ros/ros.h"

// Local
#include "complex_communication/tic_tac_toe.h"

int main(int argc, char **argv) {

        srand (time(NULL));

        ros::init(argc, argv, "player_2");

        if (argc != 1) { //no need for any input
                ROS_INFO("usage: rosrun complex_communication player_2\n");
                return 1;
        }

        ros::NodeHandle n1;

        ros::ServiceClient player2 = n1.serviceClient<complex_communication::tic_tac_toe>("tic_tac_toe");

        complex_communication::tic_tac_toe srv;

        // The node will be alive as long as the game is not over
        while (ros::ok()) {
                // Give the player's ID for the server to recognise
                srv.request.player = 2;
                srv.request.move = rand() % 9;
                if (player2.call(srv)) { // Call the service
                        //ROS_INFO("Player #2 has played! Next please :)\n");
                        // Now i can use the board from the service, print etc if needed
                } else {
                        ROS_ERROR("Failed to call service tic_tac_toe for player #2\n");
                        return 1;
                }
        }
        return 0;
}
