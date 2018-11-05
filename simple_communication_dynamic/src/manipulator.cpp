#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <cmath>       /* pow */

#include <dynamic_reconfigure/server.h>
#include <simple_communication_dynamic/dynamic_paramsConfig.h>


class manipulator
{
private:
ros::NodeHandle n;
ros::Subscriber sub;

// Get the dynamic parameters
dynamic_reconfigure::Server<simple_communication_dynamic::dynamic_paramsConfig> server;
dynamic_reconfigure::Server<simple_communication_dynamic::dynamic_paramsConfig>::CallbackType f;

int power;

public:

void Callback(const std_msgs::Int16::ConstPtr& msg)
{
        ROS_INFO("I heard [%f]", pow(msg->data, power));
        //ROS_INFO("I heard power: [%d]", power);
        //ROS_INFO("I heard: [%d]", std::pow(int(msg->data),f));
}

void dynCallback(simple_communication_dynamic::dynamic_paramsConfig &config, uint32_t level) {
        ROS_INFO("Reconfigure Request: %d", config.power);
        power = config.power;
}

manipulator(){
        f = boost::bind(&manipulator::dynCallback, this, _1, _2);

        server.setCallback(f);

        // Run the subscriber
        sub = n.subscribe("/task1/numbers", 1000, &manipulator::Callback, this);
}

};


int main(int argc, char **argv)
{
        ros::init(argc, argv, "manipulator");

        manipulator object;

        ros::spin();

        return 0;
}
