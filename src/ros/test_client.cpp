#include "ros/ros.h"
#include "scu_gpio/gpio_cmd_stt.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gpio_client");
    if (argc != 3)
    {
        ROS_INFO("Client GPIO");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<scu_gpio::gpio_cmd_stt>("gpio");
    scu_gpio::gpio_cmd_stt srv;

    int pin_index = atoll(argv[1]);
    
    if (atoll(argv[2]) == 0)
        srv.request.BOARD_PIN_CMD[pin_index] = 0x10;
    else if (atoll(argv[2]) == 1)
        srv.request.BOARD_PIN_CMD[pin_index] = 0x11;
    else if (atoll(argv[2]) == 2)
        srv.request.BOARD_PIN_CMD[pin_index] = 0x0F;

    
    ros::Time time_begin = ros::Time::now();

    if (client.call(srv))
    {
        ros::Time time_end = ros::Time::now();
        ros::Duration duration = time_end - time_begin;
        ROS_INFO("Slept for %lf secs", duration.toSec());
        for (int pin_index = 0; pin_index <= 40; pin_index++) {
            ROS_INFO("\nPIN_%d: %d", pin_index, srv.response.BOARD_PIN_STT[pin_index]);
        }
    }
    else
    {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }

    return 0;
}