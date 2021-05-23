#ifndef __POINT_H__
#define __POINT_H__
#include <cmath>

class Point
{
public:
    float x = 0;
    float y = 0;

    Point(float _x, float _y): x(_x), y(_y)
    {}

    Point(const Point& other): x(other.x), y(other.y)
    {}

    Point operator-(const Point& other) const
    {
        Point ret(*this);
        ret.x -= other.x;
        ret.y -= other.y;
        return ret;
    }

    Point operator+(const Point& other) const
    {
        Point ret(*this);
        ret.x += other.x;
        ret.y += other.y;
        return ret;
    }

    float length()
    {
        return sqrt(x*x + y*y);
    }
};

#endif // __POINT_H__
