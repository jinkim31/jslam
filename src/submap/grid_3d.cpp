//
// Created by Jin Kim on 2022/04/08.
//

#include "grid_3d.h"

Grid3D::Grid3D(const Vector3i& initialSize)
{
    ros::NodeHandle nh;
    vizPub = nh.advertise<visualization_msgs::Marker>("jslam_marker", 0);


    size = initialSize;
    allocGrid(grid, size);
    offset<< 0,0,0;

    sizeIncrement = 10;
}

Grid3D::~Grid3D()
{

}

void Grid3D::visualize()
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

    for(int x=0; x<size[0]; x++){
        for(int y=0; y<size[1]; y++){
            for(int z=0; z<size[2]; z++)
            {
                geometry_msgs::Point p;
                p.x = x + offset[0];
                p.y = y + offset[0];
                p.z = z + offset[0];

                std_msgs::ColorRGBA c;
                c.r = 1.0f;
                c.g = 1.0f;
                c.b = 1.0f;
                if(grid[x][y][z]==0.0f) continue;
                else c.a = grid[x][y][z];

                marker.points.push_back(p);
                marker.colors.push_back(c);
            }
        }
    }

    vizPub.publish(marker);
}


void Grid3D::allocGrid(Grid& grid, const Vector3i& size)
{
    grid = (double***)malloc(sizeof(double**) * size[0]);

    for(int y=0; y<size[0]; y++)
    {
        grid[y] = (double**)malloc(sizeof(double*)*size[1]);

        for(int z=0; z<size[1]; z++)
        {
            grid[y][z] = (double*)malloc(sizeof(double)* size[2]);
        }
    }
}

void Grid3D::deleteGrid(Grid& grid, const Vector3i& size)
{
    for(int y=0; y<size[0]; y++)
    {
        for(int z=0; z<size[1]; z++)
        {
            delete grid[y][z];
        }

        delete grid[y];
    }

    delete grid;
}

void Grid3D::set(const Vector3i &index, const double value, const bool& autoAllocate)
{
    Vector3i unsignedIndex = getUnsignedIndex(index);

    if(!isIndexInbound((index)))
    {
        Vector3i oldSize = size, oldOffset = offset;

        do
        {

            for(int dir=0; dir<3; dir++)
            {
                if (unsignedIndex[dir] < 0)
                {
                    size[dir] = size[dir] + sizeIncrement;
                    offset[dir] = offset[dir] - sizeIncrement;
                }
                else if(size[dir] <= unsignedIndex[dir])
                {
                    size[dir] = size[dir] + sizeIncrement;
                }
            }

            cout<<"size updated to:\n"<<size<<endl;
        }while(!isIndexInbound(index));

        Grid newGrid;
        allocGrid(newGrid, size);

        deleteGrid(grid, oldSize);

        grid = newGrid;

        unsignedIndex = getUnsignedIndex(index);
    }


    grid[unsignedIndex[0]][unsignedIndex[1]][unsignedIndex[2]] = value;
}

const double Grid3D::get(const Vector3i &index)
{
    return 0;
}
