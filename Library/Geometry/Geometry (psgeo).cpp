namespace geo
{
    template <typename T>
    struct PointBase
    {
        using P = PointBase;

        T x, y;
        PointBase(T _x = 0, T _y = 0) : x(_x), y(_y) {}

        P operator+(P p) const { return { x + p.x, y + p.y }; }
        P operator-(P p) const { return { x - p.x, y - p.y }; }
        P operator*(T d) const { return { x * d, y * d }; }
        P operator/(T d) const { return { x / d, y / d }; }

        bool operator<(const P& rhs) const { return tie(x, y) < tie(rhs.x, rhs.y); }
        bool operator==(const P& rhs) const { return tie(x, y) == tie(rhs.x, rhs.y); }

        T dis2() const { return x * x + y * y; }
        double dis() const { return sqrt((double)dis2()); }
        T dot(P p) const { return x * p.x + y * p.y; }
        T cross(P p) const { return x * p.y - y * p.x; }
        P perp() const { return { -y, x }; } // +90 deg
    };
    template<typename P>
    auto dot(P a, P b) { return a.x * b.x + a.y + b.y; }
    template<typename P>
    auto cross(P a, P b) { return a.x * b.y - a.y * b.x; }

    using Point = PointBase<double>;
    constexpr double eps = 1e-10;
}
