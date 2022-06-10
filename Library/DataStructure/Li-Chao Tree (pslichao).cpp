template <bool isMax = false>
struct LiChao
{
    struct Line
    {
        ll a, b; // y = ax + b
        ll getvalue(ll x)
        {
            return x * a + b;
        }
    };
    Line empty;

    struct Node
    {
        int l = -1, r = -1;
        ll xl, xr;
        Line line;
    };

    vector<Node> d;

    void init(ll xmin, ll xmax)
    {
        empty.a = 0;
        empty.b = isMax ? -INF : INF;
        d.push_back({ -1, -1, xmin, xmax, empty });
    }

    void insert(Line line, int node)
    {
        ll xl = d[node].xl;
        ll xr = d[node].xr;
        Line low = d[node].line;
        Line high = line;
        if(low.getvalue(xl) > high.getvalue(xl)) swap(low, high);

        if(low.getvalue(xr) <= high.getvalue(xr)) {
            d[node].line = isMax ? high : low;
            return;
        }

        ll xm = (xl + xr) / 2;
        if(low.getvalue(xm) > high.getvalue(xm)) {
            // 왼쪽에 교점
            d[node].line = isMax ? low : high;
            if(d[node].l == -1) {
                d[node].l = d.size();
                d.push_back({ -1, -1, xl, xm, empty });
            }
            insert(low, d[node].l);
        } else {
            // 오른쪽에 교점
            d[node].line = isMax ? high : low;
            if(d[node].r == -1) {
                d[node].r = d.size();
                d.push_back({ -1, -1, xm + 1, xr, empty });
            }
            insert(high, d[node].r);
        }
    }

    ll get(ll x, int node)
    {
        if(node == -1) return empty.b;

        ll xl = d[node].xl;
        ll xr = d[node].xr;
        ll xm = (xl + xr) / 2;
        ll res = d[node].line.getvalue(x);

        ll cv;
        if(x <= xm) cv = get(x, d[node].l);
        else cv = get(x, d[node].r);

        if(isMax == false) res = min(res, cv);
        else res = max(res, cv);
        return res;
    }
};
