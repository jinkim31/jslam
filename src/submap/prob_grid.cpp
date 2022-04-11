//
// Created by Jin Kim on 2022/04/01.
//

#include "prob_grid.h"

ProbGrid::ProbGrid()
{
    ros::NodeHandle nh;
    this->vizPub = nh.advertise<visualization_msgs::Marker>("jslam_grid", 0);
}

void ProbGrid::addScan(sensor_msgs::PointCloud2 &pointCloud)
{

}

void ProbGrid::visualize()
{
    visualization_msgs::MarkerArray array;
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time();
    marker.ns = "jslam";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE_LIST;
    marker.action = visualization_msgs::Marker::ADD;
    for(int i=0; i<10; i++)
    {
        geometry_msgs::Point p;
        p.x = i;
        p.y = i;
        p.z = i;
        marker.points.push_back(p);
    }
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 1;
    marker.scale.y = 1;
    marker.scale.z = 1.0;
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 1.0;
    marker.color.a = 1.0;
    vizPub.publish(marker);
}
