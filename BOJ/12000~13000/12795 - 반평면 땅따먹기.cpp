#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 4000000000000000000;

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

    struct Node
    {
        int l = -1, r = -1;
        ll xl, xr;
        Line line;
    };

    vector<Node> d;

    void init(ll xmin, ll xmax)
    {
        d.push_back({ -1, -1, xmin, xmax, { 0, -INF } });
    }

    void insert(Line line, int node)
    {
        ll xl = d[node].xl;
        ll xr = d[node].xr;
        Line low = d[node].line;
        Line high = line;
        if(low.getvalue(xl) > high.getvalue(xl)) swap(low, high);

        if(low.getvalue(xr) <= high.getvalue(xr)) {
            d[node].line = high;
            return;
        }

        ll xm = (xl + xr) / 2;
        if(low.getvalue(xm) > high.getvalue(xm)) {
            // 왼쪽에 교점
            d[node].line = low;
            if(d[node].l == -1) {
                d[node].l = d.size();
                d.push_back({ -1, -1, xl, xm, { 0, -INF } });
            }
            insert(high, d[node].l);
        } else {
            // 오른쪽에 교점
            d[node].line = high;
            if(d[node].r == -1) {
                d[node].r = d.size();
                d.push_back({ -1, -1, xm + 1, xr, { 0, -INF } });
            }
            insert(low, d[node].r);
        }
    }

    ll get(ll x, int node)
    {
        if(node == -1) return -INF;

        ll xl = d[node].xl;
        ll xr = d[node].xr;
        ll xm = (xl + xr) / 2;
        ll res = d[node].line.getvalue(x);
        if(x <= xm) res = max(res, get(x, d[node].l));
        else res = max(res, get(x, d[node].r));
        return res;
    }
};

int q;
LiChao cht;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cht.init(-1000000000000, 1000000000000);
    cin >> q;
    for(int i = 0; i < q; ++i) {
        ll a, b, c;
        cin >> a;
        if(a == 1) {
            cin >> b >> c;
            cht.insert({ b, c }, 0);
        } else {
            cin >> b;
            cout << cht.get(b, 0) << "\n";
        }
    }

    return 0;
}
