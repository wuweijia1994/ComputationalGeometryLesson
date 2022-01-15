#include <point.h>
#include <cg_math.h>

float cross_2d(const Point &l, const Point &r)
{
    return l.x * r.y - l.y * r.x;
}

bool if_turn_left(const Point &first, const Point &middle, const Point &last)
{
    float ret = cross_2d(middle - first, last - middle);
    return ret >= 0;
}