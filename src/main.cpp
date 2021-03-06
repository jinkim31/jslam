#include <iostream>
#include <ros/ros.h>
#include "gradient_solver/gradient_solver.h"
#include "submap/prob_grid.h"
#include "submap/grid_3d.h"
#include <vector>
#include <sensor_msgs/PointCloud2.h>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "jslam");
    ros::NodeHandle nh;

    ProbGrid probGrid;
    sensor_msgs::PointCloud2 msg;



    ros::Rate loop_rate(2);
    while (ros::ok())
    {
        probGrid.clear();
        probGrid.addScan(msg);
        probGrid.visualize();


        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}