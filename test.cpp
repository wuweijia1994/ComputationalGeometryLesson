#include <cstdio>
#include <vector>
#include "point.h"
#include "search.h"

int main()
{
    std::vector<Point> data = {Point(0, 0), Point(0, 1), Point(0.5, 0.5), Point(1, 1), Point(1, 0)};
    std::vector<Point> convex_hull;
    search_convex_hull(data, convex_hull);
    for(auto& pt : convex_hull)
    {
        printf("Point: [%f, %f]\n", pt.x, pt.y);
    }
    return 0;
}