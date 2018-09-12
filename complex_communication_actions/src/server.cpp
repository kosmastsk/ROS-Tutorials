#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <complex_communication_actions/tictactoeAction.h>

int plays = 0; // global variable to count the number of rounds

static int board[9]; // global static variable for the table

// Two variables that create the order of playing between the players
int player1_canplay = 0;
int player2_canplay = 0;

int can_play[2] = {1, 0}; //position 0 is for player 1 and position 1 for player 2

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

// Function that prints the result
void print(int board[9]){
        ROS_INFO("|_%d_|_%d_|_%d_|",board[0], board[1], board[2]);
        ROS_INFO("|_%d_|_%d_|_%d_|",board[3], board[4], board[5]);
        ROS_INFO("|_%d_|_%d_|_%d_|\n", board[6], board[7], board[8]);
}

class tictactoeAction
{
protected:

ros::NodeHandle nh_;
actionlib::SimpleActionServer<complex_communication_actions::tictactoeAction> as_;   // NodeHandle instance must be created before this line. Otherwise strange error occurs.
std::string tictactoe_action_;
// create messages that are used to published feedback/result
complex_communication_actions::tictactoeFeedback feedback_;
complex_communication_actions::tictactoeResult result_;

public:

tictactoeAction(std::string name) :
        as_(nh_, name, boost::bind(&tictactoeAction::executeCB, this, _1), false),
        tictactoe_action_(name)
{
        as_.start();
}

~tictactoeAction(void)
{
}

void executeCB(const complex_communication_actions::tictactoeGoalConstPtr &goal)
{
        // helper variables
        ros::Rate r(1);
        bool success = true;

        // start executing the action
        while (can_play[goal->player-1] == 1) {                 // Check if is my turn to play

                // check that preempt has not been requested by the client
                if (as_.isPreemptRequested() || !ros::ok())
                {
                        ROS_INFO("%s: Preempted", tictactoe_action_.c_str());
                        // set the action state to preempted
                        as_.setPreempted();
                        success = false;
                        break;
                }

                ROS_INFO("\n\n Now is player #%d\n", goal->player);

                ROS_INFO("Request by player %d: Play in position %d\n", goal->player, goal->move);

                int occupied = 0;                 //Flag for knowing if the place is available

                if (board[goal->move] != 0) {
                        occupied = 1;
                        ROS_INFO("This place is occupied. Please try a valid position\n");
                        break;
                }
                else{                 // I can play
                        ROS_INFO("This move is valid.\n");
                        plays++;
                        board[goal->move] = goal->player;

                        // Let the other player play
                        if (goal->player == 1) {
                                can_play[goal->player-1] = 0;
                                can_play[goal->player] = 1;
                        }
                        else if (goal->player == 2) {
                                can_play[goal->player-2] = 1;
                                can_play[goal->player-1] = 0;
                        }

                        print(board);

                        // Save the new board as the feedback of the action
                        for (int i = 0; i < 9; i++) {
                                feedback_.current_table[i] = board[i];
                        }

                        // publish the feedback
                        as_.publishFeedback(feedback_);

                        // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
                        r.sleep();
                }
                if(success)
                {
                        result_.final_table = feedback_.current_table;
                        ROS_INFO("%s: Succeeded", tictactoe_action_.c_str());
                        // set the action state to succeeded
                        as_.setSucceeded(result_);
                }
        }

        if (game_finished(board, goal->player)) {
                ROS_INFO("We have a winner! Player #%d\n", goal->player);
                print(board);
                ros::shutdown();
        }
        else if (plays == 9) {
                ROS_INFO("We have a draw!\n");
                print(board);
                ros::shutdown();
        }
}
};

int main(int argc, char** argv)
{
        ros::init(argc, argv, "server");

        tictactoeAction server("tictactoe");
        ros::spin();

        return 0;
}
