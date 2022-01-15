#ifndef __POINT_H__
#define __POINT_H__
#include <math.h>

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
};

#endif // __POINT_H__
