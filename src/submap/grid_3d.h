#ifndef JSLAM_GRID_3D_H
#define JSLAM_GRID_3D_H

#include <vector>
#include <eigen3/Eigen/Dense>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

using namespace std;
using namespace Eigen;

class Grid3D
{
    using Grid = double***;
private:
    Grid grid;
    Vector3i size;
    Vector3i offset;
    size_t sizeIncrement;
    ros::Publisher vizPub;

    void allocGrid(Grid& grid, const Vector3i& size);
    void deleteGrid(Grid& grid, const Vector3i& size);
    void copyGrid(Grid& des, const Vector3i& desOffset, const Grid& src, const Vector3i& srcSize, const Vector3i srcOffset);

public:
    Grid3D(const Vector3i& initialSize);
    Grid3D();
    ~Grid3D();

    inline const Vector3i getSize(){return size;}
    inline const Vector3i getOffset(){return offset;}
    inline Vector3i getUnsignedIndex(const Vector3i& signedIndex){return signedIndex - offset;}
    inline bool isIndexInbound(const Vector3i& signedIndex)
    {
        Vector3i unsignedIndex = getUnsignedIndex(signedIndex);
        return (
        (0 <= unsignedIndex[0] && unsignedIndex[0] < size[0]) &&
        (0 <= unsignedIndex[1] && unsignedIndex[1] < size[1]) &&
        (0 <= unsignedIndex[2] && unsignedIndex[2] < size[2]));
    }

    inline bool isUnsignedIndexInbound(const Vector3i& unsignedIndex)
    {
        return (
        (0 <= unsignedIndex[0] && unsignedIndex[0] < size[0]) &&
        (0 <= unsignedIndex[1] && unsignedIndex[1] < size[1]) &&
        (0 <= unsignedIndex[2] && unsignedIndex[2] < size[2]));
    }

    void set(const Vector3i& index, const double value, const bool& autoAllocate = false);
    const double get(const Vector3i& index);
};


#endif //JSLAM_GRID_3D_H
