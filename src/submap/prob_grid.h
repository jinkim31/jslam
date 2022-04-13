#ifndef JSLAM_PROB_GRID_H
#define JSLAM_PROB_GRID_H

#include <cmath>
#include <sensor_msgs/PointCloud2.h>
#include <vector>
#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <eigen3/Eigen/Dense>
#include "grid_3d.h"

using namespace std;
using namespace Eigen;

class ProbGrid
{
private:
    Grid3D grid;
    ros::Publisher vizPub;
public:
    ProbGrid();
    ~ProbGrid();
    void addScan(sensor_msgs::PointCloud2& pointCloud);
    void visualize();
    void clear();
    inline int getGridIndex(double x){return floor(x);}
};


#endif //JSLAM_PROB_GRID_H
