#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include "serialFriend.h"
#include "platform_defs.h"
#include "stdio.h"
#include "packets.h"
#include <unistd.h>
#include <pthread.h>
#include "capybara.h"

int i=0;

Capybara* capybot=0;
void joystickCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    //ROS_INFO("Translation: [%f] Rotation [%f]", msg->linear.x, msg->angular.z);
    float numba = 50.0f;
    capybot->setWheelSpeed(numba*msg->linear.x, numba*msg->linear.x);
}


void *Run(void* context)
{

    while(1)
    {
        Capybara* c=(Capybara*)context;
        c->handleCommunication();
    }
    return NULL;
}



int main(int argc, char **argv)
{
    PacketHandler_init();
    capybot = new Capybara();
    capybot->openConnection(argv[1]);
    Packets_init();
    printf("opening %s \n",argv[1]);
    pthread_t threads[1];
    pthread_create(&threads[0], NULL, Run,capybot);
    printf("Startin up...\n");
    ros::init(argc, argv, "capybara");
    printf("Init...\n");
    ros::NodeHandle n;
    printf("Node handle...\n");
    ros::Subscriber sub = n.subscribe("/cmd_vel", 1000, joystickCallback);
    printf("Subscribed!\n");
    ros::spin();

    return 0;
}

