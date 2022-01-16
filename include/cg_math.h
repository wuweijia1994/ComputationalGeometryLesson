#include <point.h>
#include <edge.h>

enum TurnDir
{
    Parallel,
    Left,
    Right
};

float cross_2d(const Point &l, const Point &r);

bool if_turn_left(const Point &first, const Point &middle, const Point &last);

TurnDir cal_turn_dir(const Point &first, const Point &middle, const Point &last);

bool if_cross(const Edge &l, const Edge &r);

float calculate_distance(const Point &l, const Point &r);