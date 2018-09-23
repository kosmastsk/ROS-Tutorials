#include "ros/ros.h"

#include "std_msgs/String.h"
#include "simple_robot_msgs/TemperatureReading.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/* This node simulates the thermal sensor
 *  It sends messages of type TemperatureReading.msg in the /sensors/temperature
 */
int main(int argc, char **argv)
{
        ros::init(argc, argv, "thermal_sensor");

        ros::NodeHandle n;

        // Subscribe to the specific topic messages of type simple_robot_msgs::TemperatureReading
        ros::Publisher chatter_pub = n.advertise<simple_robot_msgs::TemperatureReading>("/sensors/temperature", 1000);

        // Send a value every second
        ros::Rate loop_rate(1);

        srand (time(NULL));

        while (ros::ok())
        {
                simple_robot_msgs::TemperatureReading msg;

                // Random value between 20 and 40
                msg.temperature = rand()%((40 - 20) + 1) + 20;

                ROS_INFO("%f", msg.temperature);

                chatter_pub.publish(msg);

                ros::spinOnce();

                loop_rate.sleep();
        }
        return 0;
}
