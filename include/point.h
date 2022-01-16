#ifndef __POINT_H__
#define __POINT_H__
#include <math.h>
#include <vector>
#include <memory>

class Edge;
using EdgePtr = std::shared_ptr<Edge>;

class Point
{
public:
    float x = 0.0f;
    float y = 0.0f;

    Point(float _x, float _y) : x(_x), y(_y)
    {
    }

    Point(const Point &other) : x(other.x), y(other.y)
    {
    }

    Point operator-(const Point &other) const
    {
        Point ret(*this);
        ret.x -= other.x;
        ret.y -= other.y;
        return ret;
    }

    Point operator+(const Point &other) const
    {
        Point ret(*this);
        ret.x += other.x;
        ret.y += other.y;
        return ret;
    }

    float length()
    {
        return sqrt(x * x + y * y);
    }

    bool operator()(const Point &lhs, const Point &rhs) const
    {
        if (lhs.x == rhs.x)
        {
            return lhs.y < rhs.y;
        }
        return lhs.x < rhs.x;
    }

    bool operator==(const Point &other) const
    {
        return (std::abs(this->x - other.x) + std::abs(this->y - other.y)) < 1e-6;
    }

    std::vector<EdgePtr> get_edges() const
    {
        return this->edges_;
    }

private:
    std::vector<EdgePtr> edges_;
};

#endif // __POINT_H__
