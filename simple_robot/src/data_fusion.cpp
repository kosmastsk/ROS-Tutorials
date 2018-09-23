#include "ros/ros.h"

#include "simple_robot_msgs/TemperatureReading.h"
#include "simple_robot_msgs/VictimFound.h"

const float threshold = 37;
/* This ROS node filters the information from the sensor and sends a message
 * to the victim_found topic in case the temperature surpasses a threshold
 *
 */

/* Create a class that will be responsible for publishing and subscribing
 *  This class also has methods for checking the input temperature and depending on its value, write to another topic
 */

class pubSub
{
private:
ros::Publisher pub;
ros::Subscriber sub;
ros::NodeHandle n;

public:
pubSub(){
        pub = n.advertise<simple_robot_msgs::VictimFound>("/data_fusion/victim_found", 1000);

        sub = n.subscribe("/sensors/temperature", 1000, &pubSub::callback, this); // Different that what usually looks like, without a class
}

void callback(const simple_robot_msgs::TemperatureReading::ConstPtr& msg)
{
        ROS_INFO("I heard: [%f]", msg->temperature);
        publishDataIfOverThreshold(msg->temperature);
}

void publishDataIfOverThreshold(float temp){
        if (temp > threshold) {
                simple_robot_msgs::VictimFound sensor_type;
                sensor_type.sensor = "thermal";
                pub.publish(sensor_type);
        }
}

};


int main(int argc, char **argv)
{
        ros::init(argc, argv, "data_fusion");

        pubSub object;

        ros::spin();

        return 0;
}
