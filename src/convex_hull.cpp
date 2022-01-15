#include <cstdio>
#include <algorithm>
#include <vector>
#include <point.h>
#include <cg_math.h>

bool search_convex_hull(const std::vector<Point> &_all_pts, std::vector<Point> &_convex_pts)
{
    _convex_pts.clear();
    if (_all_pts.empty())
    {
        return false;
    }

    auto y_comp = [](const Point &l, const Point &r)
    {
        return l.y < r.y;
    };

    std::vector<Point> pts;
    pts.insert(pts.end(), _all_pts.begin(), _all_pts.end());
    auto y_iter = std::min_element(pts.begin(), pts.end(), y_comp);
    std::swap(pts[0], pts[y_iter - pts.begin()]);
    Point &ref = pts[0];

    auto angle_comp = [ref](const Point &l, const Point &r)
    {
        auto first_seg = l - ref;
        auto second_seg = r - ref;

        float ret = cross_2d(first_seg, second_seg);
        if (std::abs(ret) > 0.001)
        {
            return ret > 0;
        }
        else
        {
            return first_seg.x < second_seg.x;
        }
    };

    std::sort(pts.begin() + 1, pts.end(), angle_comp);

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
            _convex_pts.push_back(pts[i]);
        }
        else
        {
            _convex_pts.pop_back();
            i--;
        }
    }

    return true;
}

bool search_unconvex_points(const std::vector<Point> &_all_pts, std::vector<Point> &_unconvex_pts)
{
    std::vector<Point> convex_pts;
    _unconvex_pts.clear();
    if (_all_pts.empty())
    {
        return false;
    }

    auto y_comp = [](const Point &l, const Point &r)
    {
        return l.y < r.y;
    };

    std::vector<Point> pts;
    pts.insert(pts.end(), _all_pts.begin(), _all_pts.end());
    auto y_iter = std::min_element(pts.begin(), pts.end(), y_comp);
    std::swap(pts[0], pts[y_iter - pts.begin()]);
    Point &ref = pts[0];

    auto angle_comp = [ref](const Point &l, const Point &r)
    {
        auto first_seg = l - ref;
        auto second_seg = r - ref;

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

    for (size_t i = 0; i < pts.size(); i++)
    {
        if (i < 2)
        {
            convex_pts.push_back(pts[i]);
            continue;
        }

        size_t last_idx = convex_pts.size() - 1;
        if (if_turn_left(convex_pts[last_idx - 1], convex_pts[last_idx], pts[i]))
        {
            convex_pts.push_back(pts[i]);
        }
        else
        {
            _unconvex_pts.push_back(convex_pts.back());
            convex_pts.pop_back();
            i--;
        }
    }

    return true;
}