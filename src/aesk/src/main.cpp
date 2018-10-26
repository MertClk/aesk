#include <iostream>
#include <ros/ros.h>

int main(int argc, char **argv){

  std::cout << std::fixed;
  std::cout << std::setprecision(10);

  ros::init(argc, argv, "navi_node");
  ros::NodeHandle nh;

//  ToDo create your object here


  ros::spin();
}