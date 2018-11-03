
#include <aesk/Aesk.h>

#include "aesk/Aesk.h"

Aesk::Aesk(ros::NodeHandle &nh_in) : nh_(nh_in) {

}

void Aesk::Start() {
// Start function is called just once, this function starts publishers and subcribers
// For more information about point cloud and image publisher and subscriber please check links below
// http://wiki.ros.org/pcl/Overview
// http://wiki.ros.org/image_transport/Tutorials/SubscribingToImages
// http://wiki.ros.org/image_transport/Tutorials/PublishingImages

  sub_cloud_in_ = nh_.subscribe<sensor_msgs::PointCloud2>(
    "/kitti/velo/pointcloud", 1, &Aesk::VelodyneCallback, this);


  pub_cloud_processed_ = nh_.advertise<sensor_msgs::PointCloud2>(
    "/cloud_processed", 1);
  pub_cloud_groundless_ = nh_.advertise<sensor_msgs::PointCloud2>(
    "/cloud_groundless", 1);
  pub_cloud_clusters_ = nh_.advertise<sensor_msgs::PointCloud2>(
    "/cloud_clusters", 1);

  image_transport::ImageTransport it_(nh_);
  sub_img_ = it_.subscribe("/kitti/camera_color_left/image_raw", 1,
                           &Aesk::ImageCallback, this);

  pub_img_ = it_.advertise("/camera/repeat", 1);

}

void Aesk::VelodyneCallback(const sensor_msgs::PointCloud2::ConstPtr &msg_in) {

  PclStuff::Cloud::Ptr cloud_msg_in(new PclStuff::Cloud);
  pcl::fromROSMsg(*msg_in, *cloud_msg_in);
  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*cloud_msg_in, *cloud_msg_in, indices);

  PclStuff::Cloud::Ptr cloud_downsampled(new PclStuff::Cloud);
  cloud_downsampled = PclStuff::Downsample(cloud_msg_in, 0.05);

  PclStuff::Cloud::Ptr cloud_groundless(new PclStuff::Cloud);
  cloud_groundless = PclStuff::GroundRemover(cloud_downsampled, 0.2);

  PclStuff::Cloud::Ptr cloud_clusters(new PclStuff::Cloud);
  PclStuff::Cloud::Ptr cloud_cluster_Centroids(new PclStuff::Cloud);
  std::vector<float> vec1, vec2, vec3;

//  ToDo finetune the clusterer parameters
  std::tie(cloud_clusters, cloud_cluster_Centroids, vec1, vec2,
           vec3) = PclStuff::MiniClusterer(cloud_groundless, 0.15, 8, 1000, 2,
                                           2, 2, 0.1, 0.1, 0.1);


  sensor_msgs::PointCloud2 cloud_out;
  pcl::toROSMsg(*cloud_downsampled, cloud_out);
  cloud_out.header.stamp = ros::Time::now();
  cloud_out.header.frame_id = "velo_link";
  pub_cloud_processed_.publish(cloud_out);

  sensor_msgs::PointCloud2 msg_groundless;
  pcl::toROSMsg(*cloud_groundless, msg_groundless);
  msg_groundless.header.stamp = ros::Time::now();
  msg_groundless.header.frame_id = "velo_link";
  pub_cloud_groundless_.publish(msg_groundless);

  sensor_msgs::PointCloud2 msg_cluster;
  pcl::toROSMsg(*cloud_clusters, msg_cluster);
  msg_cluster.header.stamp = ros::Time::now();
  msg_cluster.header.frame_id = "velo_link";
  pub_cloud_clusters_.publish(msg_cluster);


}

void Aesk::ImageCallback(const sensor_msgs::ImageConstPtr &msg_img) {

  sensor_msgs::Image msg_img_out = *msg_img;
//  In order to process the images with OpenCV library please check
// http://wiki.ros.org/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages
  msg_img_out.header.stamp = ros::Time::now();
  pub_img_.publish(msg_img_out);
}


