// player_1.cpp
// ROS
#include "ros/ros.h"
#include <unistd.h>
// Local
#include "complex_communication/tic_tac_toe.h"

static int board[9];

// Implement tic tac toe's rules for checking the winner
bool game_finished(int board[9]){
    if (board[0] == 2 && board[1] == 2 && board[2] == 2)
        return true;
    else if (board[3] == 2 && board[4] == 2 && board[5] == 2)
        return true;
    else if (board[6] == 2 && board[7] == 2 && board[8] == 2)
        return true;
    else if (board[0] == 2 && board[3] == 2 && board[6] == 2)
        return true;
    else if (board[1] == 2 && board[4] == 2 && board[7] == 2)
        return true;
    else if (board[2] == 2 && board[5] == 2 && board[8] == 2)
        return true;
    else if (board[0] == 2 && board[4] == 2 && board[8] == 2)
        return true;
    else if (board[2] == 2 && board[4] == 2 && board[6] == 2)
        return true;

    return false;
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "player_2");

    if (argc != 1) { //no need for any input
        ROS_INFO("usage: rosrun complex_communication player_2");
        return 1;
    }

    int finished = 0;
    int plays = 0;
    // The game will be finished if there is a winner or they played 9 times
    while (finished == 0 || plays == 9) {

        ros::NodeHandle n1;

        ros::ServiceClient player1 = n1.serviceClient<complex_communication::tic_tac_toe>("tic_tac_toe");

        complex_communication::tic_tac_toe srv;

        for ( size_t i = 0; i < 9; ++i ) {
            srv.request.table.data[i] = board[i]; //prepare the request with the table's content
        }

        // Give the player's ID for the server to recognise
        srv.request.player = 2;

        if (player1.call(srv)) { // Call the service
            ROS_INFO("Service called");
            board[srv.response.move] = 1; // Place the player's move on the table, the rest of the positions are same
            ROS_INFO("Player #1 has played! Next please :)");
        } else {
            ROS_ERROR("Failed to call service tic_tac_toe");
            return 1;
        }
        plays++;
        finished = game_finished(board); //Check if the game has finished after this move
    }
    usleep(10000000000000000000000000000000000000000000000);
    // Game has finished and player 2 is the winner
    ROS_INFO("Player #2 is the winner! Congrats!\n");
slee
    return 0;
}
