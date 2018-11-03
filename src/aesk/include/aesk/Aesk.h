#ifndef AESK_AESK_H
#define AESK_AESK_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "aesk/PclStuff.h"



class Aesk {
public:
  explicit Aesk(ros::NodeHandle &nh_in);
  void Start();

private:

  ros::NodeHandle &nh_;

//  Create ros subscriber

  ros::Subscriber sub_cloud_in_;
  image_transport::Subscriber sub_img_;

  //  Create ros publisher

  ros::Publisher pub_cloud_processed_;
  ros::Publisher pub_cloud_groundless_;
  ros::Publisher pub_cloud_clusters_;
  image_transport::Publisher pub_img_;

  void VelodyneCallback(const sensor_msgs::PointCloud2::ConstPtr &msg_in);
  void ImageCallback(const sensor_msgs::ImageConstPtr &msg_img);
};


#endif //AESK_AESK_H
