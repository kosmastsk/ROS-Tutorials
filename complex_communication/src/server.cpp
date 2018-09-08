// server.cpp
// System
#include <unistd.h>

// ROS
#include "ros/ros.h"

// Local
#include "complex_communication/tic_tac_toe.h"

int plays = 0;

static int board[9];

// Two variables that create the order of playing between the players
int player1_canplay = 0;
int player2_canplay = 0;

int can_play[2] = {1, 0}; //position 0 is for player 1 and position 1 for player 2

// Function that prints the result
void print(int board[9]){
        ROS_INFO("|_%d_|_%d_|_%d_|",board[0], board[1], board[2]);
        ROS_INFO("|_%d_|_%d_|_%d_|",board[3], board[4], board[5]);
        ROS_INFO("|_%d_|_%d_|_%d_|\n", board[6], board[7], board[8]);
}

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

        if (can_play[req.player-1] == 1) { // Check if is my turn to play

                ROS_INFO("\n\n Now is player #%d\n", req.player);

                ROS_INFO("Request by player %d: Play in position %d\n", req.player, req.move);

                int occupied = 0; //Flag for knowing if the place is available

                if (board[req.move] != 0) {
                        occupied = 1;
                        ROS_INFO("This place is occupied. Please try a valid position\n");
                        return true;
                }
                else{ // I can play
                        ROS_INFO("This move is valid.\n");
                        plays++;
                        board[req.move] = req.player;

                        // Let the other player play
                        if (req.player == 1) {
                                can_play[req.player-1] = 0;
                                can_play[req.player] = 1;
                        }
                        else if (req.player == 2) {
                                can_play[req.player-2] = 1;
                                can_play[req.player-1] = 0;
                        }

                        print(board);

                        // Save the new board as the response of the service
                        for (int i = 0; i < 9; i++) {
                                res.table[i] = board[i];
                        }
                }
        }

        if (game_finished(board, req.player)) {
                ROS_INFO("We have a winner! Player #%d\n", req.player);
                print(board);
                ros::shutdown();
        }
        else if (plays == 9) {
                ROS_INFO("We have a draw!\n");
                print(board);
                ros::shutdown();
        }

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
