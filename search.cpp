#include <cstdio>
#include <algorithm>
#include <vector>
#include "point.h"

float cross_2d(const Point &l, const Point &r)
{
    return l.x * r.y - l.y * r.x;
}

bool if_turn_left(const Point &first, const Point &middle, const Point &last)
{
    float ret = cross_2d(middle - first, last - middle);
    return ret >= 0;
}

bool search_convex_hull(const std::vector<Point> &_all_pts, std::vector<Point> &_convex_pts)
{
    _convex_pts.clear();
    if (_all_pts.empty())
    {
        return false;
    }

    auto bottom_left_comp = [](const Point &l, const Point &r)
    {
        if (std::abs(l.y - r.y) > 0.001)
        {
            return l.y < r.y;
        }
        else
        {
            return l.x < r.x;
        }
    };

    std::vector<Point> pts;
    pts.insert(pts.end(), _all_pts.begin(), _all_pts.end());
    auto iter = std::min_element(pts.begin(), pts.end(), bottom_left_comp);

    auto angle_comp = [iter](const Point &l, const Point &r)
    {
        auto first_seg = l - *iter;
        auto second_seg = r - *iter;
        if (first_seg.length() < 0.001)
        {
            return true;
        }

        if (second_seg.length() < 0.001)
        {
            return false;
        }

        float ret = cross_2d(first_seg, second_seg);
        if (std::abs(ret) > 0.001)
        {
            return ret > 0;
        }
        else
        {
            return first_seg.x > second_seg.x;
        }
    };

    std::sort(pts.begin(), pts.end(), angle_comp);

    for (auto &pt : pts)
    {
        printf("%f, %f\n", pt.x, pt.y);
    }

    for (size_t i = 0; i < pts.size(); i++)
    {
        if (i < 2)
        {
            _convex_pts.push_back(pts[i]);
            continue;
        }

        size_t last_idx = _convex_pts.size() - 1;
        if (if_turn_left(_convex_pts[last_idx - 1], _convex_pts[last_idx], pts[i]))
        {
            printf("left convex %d -> [%f, %f]\n", last_idx, _convex_pts[last_idx-1].x, _convex_pts[last_idx-1].y);
            printf("left convex %d -> [%f, %f]\n", last_idx, _convex_pts[last_idx].x, _convex_pts[last_idx].y);
            printf("left %d -> [%f, %f]\n", i, pts[i].x, pts[i].y);
            _convex_pts.push_back(pts[i]);
        }
        else
        {
            printf("else %d -> [%f, %f]\n", i, pts[i].x, pts[i].y);
            _convex_pts.pop_back();
            i--;
        }
    }

    return true;
}