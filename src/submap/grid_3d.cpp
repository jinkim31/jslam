//
// Created by Jin Kim on 2022/04/08.
//

#include "grid_3d.h"

Grid3D::Grid3D(const Vector3i& initialSize)
{
    size = initialSize;
    allocGrid(grid, size);
    offset<< 0,0,0;

    sizeIncrement = 10;
}

Grid3D::Grid3D()
{
    size<<0,0,0;
    allocGrid(grid, size);
    offset << 0,0,0;
    sizeIncrement = 10;
}

Grid3D::~Grid3D()
{

}

void Grid3D::allocGrid(Grid& grid, const Vector3i& size)
{
    cout<<"allocation grid of size\n"<<size<<endl;
    grid = (double***)malloc(sizeof(double**) * size[0]);

    for(int y=0; y<size[0]; y++)
    {
        grid[y] = (double**)malloc(sizeof(double*)*size[1]);

        for(int z=0; z<size[1]; z++)
        {
            grid[y][z] = (double*)malloc(sizeof(double)* size[2]);
        }
    }

    for(int x=0; x<size[0]; x++)
    {
        for (int y = 0; y < size[1]; y++)
        {
            for (int z = 0; z < size[2]; z++)
            {
                grid[x][y][z] = 0.0f;
            }
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
        }while(!isIndexInbound(index));

        Grid newGrid;
        allocGrid(newGrid, size);
        copyGrid(newGrid, offset, grid, oldSize, oldOffset);
        deleteGrid(grid, oldSize);

        grid = newGrid;

        unsignedIndex = getUnsignedIndex(index);
    }

    grid[unsignedIndex[0]][unsignedIndex[1]][unsignedIndex[2]] = value;
}

const double Grid3D::get(const Vector3i &index)
{
    Vector3i unsignedIndex = getUnsignedIndex(index);
    if(isIndexInbound(index)) return grid[unsignedIndex[0]][unsignedIndex[1]][unsignedIndex[2]];
    return 0.0f;
}

void Grid3D::copyGrid(Grid3D::Grid &des, const Vector3i& desOffset, Grid3D::Grid const &src, const Vector3i &srcSize, const Vector3i srcOffset)
{
    Vector3i combinedOffset = srcOffset - desOffset;
    for(int x=0; x<srcSize[0]; x++)
    {
        for (int y = 0; y < srcSize[1]; y++)
        {
            for (int z = 0; z < srcSize[2]; z++)
            {
                des[x + combinedOffset[0]][y + combinedOffset[1]][z + combinedOffset[2]] = src[x][y][z];
            }
        }
    }
}

void Grid3D::clear()
{
    deleteGrid(grid, size);
    size << 0,0,0;
    offset << 0,0,0;
    allocGrid(grid, size);
}
