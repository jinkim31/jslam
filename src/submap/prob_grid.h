#ifndef JSLAM_PROB_GRID_H
#define JSLAM_PROB_GRID_H

#include <cmath>
#include <sensor_msgs/PointCloud2.h>
#include <vector>
#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

class ProbGrid
{
private:
    ros::Publisher vizPub;

public:
    ProbGrid();
    void addScan(sensor_msgs::PointCloud2& pointCloud);
    void visualize();
    static int getGridIndex(double x){return floor(x);}
};


#endif //JSLAM_PROB_GRID_H
