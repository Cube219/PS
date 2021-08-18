#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
class SegTree
{
public:
    struct Node
    {
        ll mx, mx2;
    };
    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { 0, 0 };
        }
    }

    void initv(int idx, int v)
    {
        t[stLeaf + idx].mx += v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node merge(Node l, Node r)
    {
        Node res;
        if(l.mx > r.mx) {
            res.mx = l.mx;
            res.mx2 = max(l.mx2, r.mx);
        } else {
            res.mx = r.mx;
            res.mx2 = max(l.mx, r.mx2);
        }
        return res;
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return { 0, 0 };
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    ll find(int l, int r)
    {
        Node res = findImpl(0, stLeaf - 1, l, r, 1);
        return res.mx + res.mx2;
    }

    void add(int idx, ll v)
    {
        int node = stLeaf + idx;
        t[stLeaf + idx].mx += v;
        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

struct Point
{
    int x, y, v;
};

int n;
Point d[300001];
SegTree<1000001> sg;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y >> d[i].v;
    }

    // x3
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.x < r.x;
    });
    vector<ll> sum;
    vector<pair<int, int>> range;
    sum.push_back(d[0].v);
    int curx = d[0].x;
    int curi = 0;
    for(int i = 1; i < n; ++i) {
        if(curx != d[i].x) {
            range.push_back({ curi, i - 1 });
            sum.push_back(0);
            curx = d[i].x;
            curi = i;
        }
        sum.back() += d[i].v;
    }
    range.push_back({ curi, n - 1 });
    sort(sum.begin(), sum.end(), greater());
    ll cursum = 0;
    for(int i = 0; i < 3 && i < sum.size(); ++i) {
        cursum += sum[i];
    }
    res = max(res, cursum);

    // x1y2
    sg.init(1000001);
    for(int i = 0; i < n; ++i) {
        sg.initv(d[i].y, d[i].v);
    }
    sg.build();
    for(auto rng : range) {
        ll cursum = 0;
        for(int i = rng.first; i <= rng.second; ++i) {
            cursum += d[i].v;
            sg.add(d[i].y, -d[i].v);
        }
        res = max(res, cursum + sg.t[1].mx + sg.t[1].mx2);
        for(int i = rng.first; i <= rng.second; ++i) {
            sg.add(d[i].y, d[i].v);
        }
    }

    // y3
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.y < r.y;
    });
    sum.clear(); range.clear();
    sum.push_back(d[0].v);
    int cury = d[0].y;
    curi = 0;
    for(int i = 1; i < n; ++i) {
        if(cury != d[i].y) {
            range.push_back({ curi, i - 1 });
            sum.push_back(0);
            cury = d[i].y;
            curi = i;
        }
        sum.back() += d[i].v;
    }
    range.push_back({ curi, n - 1 });
    sort(sum.begin(), sum.end(), greater());
    cursum = 0;
    for(int i = 0; i < 3 && i < sum.size(); ++i) {
        cursum += sum[i];
    }
    res = max(res, cursum);

    // x2y1
    sg.init(1000001);
    for(int i = 0; i < n; ++i) {
        sg.initv(d[i].x, d[i].v);
    }
    sg.build();
    for(auto rng : range) {
        ll cursum = 0;
        for(int i = rng.first; i <= rng.second; ++i) {
            cursum += d[i].v;
            sg.add(d[i].x, -d[i].v);
        }
        res = max(res, cursum + sg.t[1].mx + sg.t[1].mx2);
        for(int i = rng.first; i <= rng.second; ++i) {
            sg.add(d[i].x, d[i].v);
        }
    }

    cout << res;

    return 0;
}
