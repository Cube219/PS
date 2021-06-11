#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

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
        d.push_back({ -1, -1, xmin, xmax, { 0, INF } });
    }

    void insert(Line line, int node)
    {
        ll xl = d[node].xl;
        ll xr = d[node].xr;
        Line low = d[node].line;
        Line high = line;
        if(low.getvalue(xl) > high.getvalue(xl)) swap(low, high);

        if(low.getvalue(xr) <= high.getvalue(xr)) {
            d[node].line = low;
            return;
        }

        ll xm = (xl + xr) / 2;
        if(low.getvalue(xm) > high.getvalue(xm)) {
            // 왼쪽에 교점
            d[node].line = high;
            if(d[node].l == -1) {
                d[node].l = d.size();
                d.push_back({ -1, -1, xl, xm, high });
            }
            insert(low, d[node].l);
        } else {
            // 오른쪽에 교점
            d[node].line = low;
            if(d[node].r == -1) {
                d[node].r = d.size();
                d.push_back({ -1, -1, xm + 1, xr, low });
            }
            insert(high, d[node].r);
        }
    }

    ll get(ll x, int node)
    {
        if(node == -1) return INF;

        ll xl = d[node].xl;
        ll xr = d[node].xr;
        ll xm = (xl + xr) / 2;
        ll res = d[node].line.getvalue(x);
        if(x <= xm) res = min(res, get(x, d[node].l));
        else res = min(res, get(x, d[node].r));
        return res;
    }
};

struct Node
{
    ll w, h, idx;
};

int n;
Node d1[50001];
vector<Node> d;
ll dp[50001];
LiChao cht;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d1[i].w >> d1[i].h;
    }
    sort(d1, d1 + n, [](const Node& l, const Node& r) {
        if(l.w == r.w) return l.h < r.h;
        return l.w < r.w;
    });

    int cur = n - 1;
    for(int i = n - 2; i >= 0; --i) {
        if(d1[cur].h >= d1[i].h) continue;
        d.push_back(d1[cur]);
        cur = i;
    }
    d.push_back(d1[cur]);
    reverse(d.begin(), d.end());

    cht.init(0, 1000000);
    dp[0] = d[0].w * d[0].h;
    cht.insert({ d[0].h, 0 }, 0);
    for(int i = 1; i < d.size(); ++i) {
        dp[i] = dp[i - 1] + d[i].w * d[i].h;
        dp[i] = min(dp[i], cht.get(d[i].w, 0));
        cht.insert({ d[i].h, dp[i - 1] }, 0);
    }

    cout << dp[d.size() - 1];

    return 0;
}
