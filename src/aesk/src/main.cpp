#include <iostream>
#include <ros/ros.h>
#include "aesk/Aesk.h"

int main(int argc, char **argv){

  std::cout << std::fixed;
  std::cout << std::setprecision(10);

  ros::init(argc, argv, "aesk_node");
  ros::NodeHandle nh;

//  ToDo create your object here
  Aesk aesk(nh);
  aesk.Start();

  ros::spin();
}