//
// Created by Jin Kim on 2022/04/01.
//

#include "prob_grid.h"

#include <random>
#include <chrono>


ProbGrid::ProbGrid()
{
    ros::NodeHandle nh;
    vizPub = nh.advertise<visualization_msgs::Marker>("jslam_grid", 0);
}

void ProbGrid::addScan(sensor_msgs::PointCloud2 &pointCloud)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0, 10.0);

    Vector3i v;
    for(int i=0; i<100; i++)
    {
        v<<distribution(generator),distribution(generator),distribution(generator);
        grid.set(v, 1.0);
    }


}

void ProbGrid::visualize()
{
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time();
    marker.ns = "jslam";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE_LIST;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 1;
    marker.pose.position.y = 1;
    marker.pose.position.z = 1;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 1;
    marker.scale.y = 1;
    marker.scale.z = 1;

    Vector3i size, offset;
    size = grid.getSize();
    offset = grid.getOffset();

    cout<<"viz\n"<<size<<"\n"<<offset<<endl;
    for(int x=0; x<size[0]; x++){
        for(int y=0; y<size[1]; y++){
            for(int z=0; z<size[2]; z++)
            {
                Vector3i index;
                index<<x,y,z;

                std_msgs::ColorRGBA c;
                c.a = grid.get(index + offset);
                if(c.a == 0.0f) continue;
                c.r = 1.0f;
                c.g = 1.0f;
                c.b = 1.0f;

                geometry_msgs::Point p;
                p.x = x + offset[0];
                p.y = y + offset[0];
                p.z = z + offset[0];

                marker.points.push_back(p);
                marker.colors.push_back(c);
            }
        }
    }

    vizPub.publish(marker);
}

ProbGrid::~ProbGrid()
{

}

void ProbGrid::clear()
{
    grid.clear();
}
