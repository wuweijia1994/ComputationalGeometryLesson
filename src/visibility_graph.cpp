#include <point.h>
#include <vector>
#include <map>

using Obstacle = std::vector<Point>;
using Obstacles = std::vector<Obstacle>;

using VisibilityGraph = std::map<Point, Point>;

bool get_sorted_points();

bool build_visibility_graph(const Point &_start_pt, const Obstacles &_obs, VisibilityGraph &_ret_graph)
{
    _ret_graph.clear();

        return true;
}
