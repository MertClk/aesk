#ifndef AESK_AESK_H
#define AESK_AESK_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "PclStuff.h"
#include <pcl_conversions/pcl_conversions.h>


class Aesk {
public:
  explicit Aesk(ros::NodeHandle &nh_in);
 

private:

  ros::NodeHandle &nh_;

};


#endif //AESK_AESK_H
