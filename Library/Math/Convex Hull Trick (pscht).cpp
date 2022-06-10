struct CHT
{
    using Type = ll;

    struct Line
    {
        Type a, b; // y = ax + b
    };

    vector<Line> d;

    double getx(const Line& a, const Line& b)
    {
        return (double)(a.b - b.b) / (double)(b.a - a.a);
    }

    void insert(Type a, Type b)
    {
        Line cur = { a, b };
        while(d.size() > 1) {
            Line& b1 = d[d.size() - 1];
            Line& b2 = d[d.size() - 2];
            if(getx(cur, b1) <= getx(b1, b2)) {
                d.pop_back();
            } else {
                break;
            }
        }
        d.push_back(cur);
    }

    Type get(Type x)
    {
        int l = 0, r = d.size() - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(getx(d[m], d[m + 1]) <= x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return d[l].a * x + d[l].b;
    }
};

// min value -> a decrease
// max value -> a increase
