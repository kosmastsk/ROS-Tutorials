#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

        ros::init(argc, argv, "streamer");

        ros::NodeHandle n;

        ros::Publisher chatter_pub = n.advertise<std_msgs::Int16>("task1/numbers", 1000);

        // Get the publishing rate as a static parameter
        int pubFreq;
        if (n.hasParam("/streamer/rate"))
                n.getParam("/streamer/rate",pubFreq);
        else
        {
                ROS_WARN("[Simple Communication Dynamic] : Parameter rate not found. Using Default");
                pubFreq = 1;
        }

        ros::Rate loop_rate(pubFreq);

        int count = 0;
        while (ros::ok())
        {
                std_msgs::Int16 num;
                num.data = (rand() % 1000);
                ROS_INFO("%d", num.data);
                chatter_pub.publish(num);
                ros::spinOnce();
                loop_rate.sleep();
        }

        return 0;
}
