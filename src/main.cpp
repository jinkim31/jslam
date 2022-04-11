#include <iostream>
#include <ros/ros.h>
#include "gradient_solver/gradient_solver.h"
#include "submap/prob_grid.h"
#include "submap/grid_3d.h"
#include <vector>

#include <random>
#include <chrono>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
normal_distribution<double> distribution(0.0, 10.0);

double r()
{
    double r = distribution(generator);
    if(r < 0) return -r;
    return r;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "jslam");
    ros::NodeHandle nh;

    Eigen::Vector3i initialSize;
    initialSize<<10,10,10;
    Grid3D grid(initialSize);

    ros::Rate loop_rate(2);

    Eigen::Vector3i v;


    int i=0;
    v<<0,0,0;
    grid.set(v, 1);

    while (ros::ok())
    {
        v<<-i,-i,-i++;
        grid.set(v, 1);

        grid.visualize();
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}