// server.cpp
// System
#include <unistd.h>

// ROS
#include "ros/ros.h"

// Local
#include "complex_communication/tic_tac_toe.h"

int plays = 0;

// Implement tic tac toe's rules for checking the winner
bool game_finished(int board[9], int id){
    if (board[0] == id && board[1] == id && board[2] == id)
        return true;
    else if (board[3] == id && board[4] == id && board[5] == id)
        return true;
    else if (board[6] == id && board[7] == id && board[8] == id)
        return true;
    else if (board[0] == id && board[3] == id && board[6] == id)
        return true;
    else if (board[1] == id && board[4] == id && board[7] == id)
        return true;
    else if (board[2] == id && board[5] == id && board[8] == id)
        return true;
    else if (board[0] == id && board[4] == id && board[8] == id)
        return true;
    else if (board[2] == id && board[4] == id && board[6] == id)
        return true;

    return false;
}

bool play(complex_communication::tic_tac_toe::Request &req,
          complex_communication::tic_tac_toe::Response &res) {
    plays++;
    // Check who is going to play now
    if (req.player == 1){
        ROS_INFO("\n\n Now is player #%d\n", req.player);

        //Calculating the next move with a random way, between the places that are not occupied. If occupied try again
        res.move = rand() % 8;
        ROS_INFO("Request by player %d: Play in position %d", req.player, res.move);

        int occupied = 0; //Flag for knowing if the place is available

        if (req.table.data[res.move] != 0){
            occupied = 1;
            ROS_INFO("This place is occupied. Please try a valid position\n");
        }
        else{
            ROS_INFO("This place is valid.\n");
        }

        while (occupied == 1){
            res.move = rand() % 8;
            ROS_INFO("Request by player %d: Play in position %d", req.player, res.move);
            if (req.table.data[res.move] != 0){
                ROS_INFO("This place is occupied. Please try a valid position\n");
            }
            else{
                occupied = 0;
                ROS_INFO("This place is valid.\n");
            }
        }

        req.table.data[res.move] = req.player; //Update the board JUST for printing reasons

        ROS_INFO("|_%d_|_%d_|_%d_|",req.table.data[0], req.table.data[1], req.table.data[2]);

        ROS_INFO("|_%d_|_%d_|_%d_|",req.table.data[3], req.table.data[4], req.table.data[5]);

        ROS_INFO("|_%d_|_%d_|_%d_|\n\n",req.table.data[6], req.table.data[7], req.table.data[8]);

        // Now is player #2
    }

    // The game will be finished if there is a winner or they played 9 times
    //reinterpret_cast<char*>(req.table.data())

    int* table_new = reinterpret_cast<int*>(&req.table.data);

    if (game_finished(table_new, req.player)){
        ROS_INFO("We have a winner! Player #%d\n", req.player);
        ros::shutdown();
    }
    else if (plays == 9){
        ROS_INFO("We have a draw!\n");
        ros::shutdown();
    }

    usleep(1000);
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("tic_tac_toe", play);

    ROS_INFO("Tic tac toe up and running.");
    ROS_INFO("|_%d_|_%d_|_%d_|", 0, 1, 2);
    ROS_INFO("|_%d_|_%d_|_%d_|", 3, 4, 5);
    ROS_INFO("|_%d_|_%d_|_%d_|", 6, 7, 8);

    ros::spin();

    return 0;
}
