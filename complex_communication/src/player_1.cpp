// player_1.cpp
// ROS
#include "ros/ros.h"

// Local
#include "complex_communication/tic_tac_toe.h"

static int board[9];

int main(int argc, char **argv) {

    ros::init(argc, argv, "player_1");

    if (argc != 1) { //no need for any input
        ROS_INFO("usage: rosrun complex_communication player_1");
        return 1;
    }

    ros::NodeHandle n1;

    ros::ServiceClient player1 = n1.serviceClient<complex_communication::tic_tac_toe>("tic_tac_toe");

    complex_communication::tic_tac_toe srv;

    while (ros::ok()) {

        for (size_t i = 0; i < 9; ++i) {
            srv.request.table.data[i] = board[i]; //prepare the request with the table's content
        }

        // Give the player's ID for the server to recognise
        srv.request.player = 1;

        if (player1.call(srv)) { // Call the service
            ROS_INFO("Service called");
            board[srv.response.move] = 1; // Place the player's move on the table, the rest of the positions are same
            ROS_INFO("Player #1 has played! Next please :)");
        } else {
            ROS_ERROR("Failed to call service tic_tac_toe");
            return 1;
        }

    }
    return 0;
}
