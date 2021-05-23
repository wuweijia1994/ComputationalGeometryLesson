#include <vector>
#include "point.h"

float cross_2d(const Point &l, const Point &r);

bool if_turn_left(const Point &first, const Point &middle, const Point &last);

bool search_convex_hull(const std::vector<Point> &_all_pts, std::vector<Point> &_convex_pts);

bool search_unconvex_points(const std::vector<Point> &_all_pts, std::vector<Point> &_unconvex_pts);