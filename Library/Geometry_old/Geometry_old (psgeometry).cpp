struct Point
{
    ll x, y;
};
Point operator+(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}
Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}
ll dot(const Point& l, const Point& r)
{
    return l.x * r.x + l.y * r.y;
}

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

ll lensq(const Point& a, const Point& b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}
