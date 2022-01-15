#include <cstdio>
#include <random>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <matplotlib-cpp/matplotlibcpp.h>

class Point
{
public:
    float x = 0;
    float y = 0;

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

    auto x_comp = [](const Point &l, const Point &r)
    {
        return l.x < r.x;
    };

    auto y_comp = [](const Point &l, const Point &r)
    {
        return l.y < r.y;
    };

    std::vector<Point> pts;
    pts.insert(pts.end(), _all_pts.begin(), _all_pts.end());
    auto x_iter = std::min_element(pts.begin(), pts.end(), x_comp);
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

void convert(const std::vector<Point> &data, std::vector<double> &x, std::vector<double> &y)
{
    x.clear();
    y.clear();

    for (const auto &pt : data)
    {
        x.push_back(pt.x);
        y.push_back(pt.y);
    }
}

int main()
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    std::vector<Point> data;
    for (int i = 0; i < 20; i++)
    {
        data.push_back(Point(dist(rd), dist(rd)));
    }
    std::vector<Point> convex_hull;
    std::vector<Point> unconvex_pts;
    search_convex_hull(data, convex_hull);
    search_unconvex_points(data, unconvex_pts);

    std::vector<double> x;
    std::vector<double> y;

    namespace plt = matplotlibcpp;
    // convert(data, x, y);
    // plt::plot(x, y);

    convert(convex_hull, x, y);
    plt::plot(x, y, "r");

    convert(unconvex_pts, x, y);
    plt::scatter(x, y);

    plt::show();

    return 0;
}