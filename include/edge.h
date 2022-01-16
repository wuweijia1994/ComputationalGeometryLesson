#ifndef __EDGE_H__
#define __EDGE_H__

#include <memory>
#include <utility>

class Point;
using PointPtr = std::shared_ptr<Point>;

using EndPtsPtr = std::pair<PointPtr, PointPtr>;

class Edge
{
public:
    Edge() = delete;
    Edge(PointPtr start_pt, PointPtr end_pt)
    {
        this->end_pts.first = start_pt;
        this->end_pts.second = end_pt;
    }

    EndPtsPtr get_end_pts() const
    {
        return this->end_pts;
    }

    bool check_valid() const
    {
        return (this->end_pts.first != nullptr) && (this->end_pts.second != nullptr);
    }

private:
    EndPtsPtr end_pts;
};

#endif
