#include <point.h>
#include <cg_math.h>

float cross_2d(const Point &l, const Point &r)
{
    return l.x * r.y - l.y * r.x;
}

bool if_turn_left(const Point &first, const Point &middle, const Point &last)
{
    auto dir = cal_turn_dir(first, middle, last);
    return dir == TurnDir::Left;
}

TurnDir cal_turn_dir(const Point &first, const Point &middle, const Point &last)
{
    float ret = cross_2d(middle - first, last - middle);
    if (std::abs(ret) < 1e-6)
    {
        return TurnDir::Parallel;
    }
    if (ret > 0)
    {
        return TurnDir::Left;
    }
    else
    {
        return TurnDir::Right;
    }
}

bool if_cross(const Edge &l, const Edge &r)
{
    if (!l.check_valid() || !r.check_valid())
    {
        return false;
    }

    const auto &l_s = *(l.get_end_pts().first);
    const auto &l_e = *(l.get_end_pts().second);

    const auto &r_s = *(r.get_end_pts().first);
    const auto &r_e = *(r.get_end_pts().second);

    auto check_r_0 = cal_turn_dir(l_s, l_e, r_s);
    auto check_r_1 = cal_turn_dir(l_s, l_e, r_e);
    auto check_l_0 = cal_turn_dir(r_s, r_e, l_s);
    auto check_l_1 = cal_turn_dir(r_s, r_e, l_e);

    // if (check_l_0)

    return true;
}