#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include "serialFriend.h"

void joystickCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  ROS_INFO("Translation: [%f] Rotation [%f]", msg->linear.x, msg->angular.z);
}

int main(int argc, char **argv)
{
  SerialFriend* s= new SerialFriend("/dev/ttyUSB0",B115200);
  char c[500];
  s->read(c,200);
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
