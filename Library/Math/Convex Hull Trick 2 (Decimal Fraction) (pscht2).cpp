struct CHT
{
    struct Line
    {
        ll a, b; // y = ax + b
    };

    struct R
    {
        ll u, d;

        bool operator<=(const R& rhs) const
        {
            return u * rhs.d <= rhs.u * d;
        }
    };

    vector<Line> d;
    int pos;

    void clear()
    {
        d.clear();
        pos = 0;
    }

    R getx(const Line& a, const Line& b)
    {
        ll u = b.b - a.b;
        ll d = a.a - b.a;
        ll g = gcd(u, d);
        return { u / g, d / g };
    }

    void insert(ll a, ll b)
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

    ll get(ll x)
    {
        R rx = { x, 1 };
        int l = 0, r = d.size() - 1;
        while(l < r) {
            int m = (l + r) / 2;
            if(getx(d[m], d[m + 1]) <= rx) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return d[l].a * x + d[l].b;
    }

    ll get_mono(ll x)
    {
        while(pos < d.size() - 1 && (d[pos].b - d[pos + 1].b) < x * (d[pos + 1].a - d[pos].a)) pos++;
        return d[pos].a * x + d[pos].b;
    }
};

// min value -> a decrease
// max value -> a increase
