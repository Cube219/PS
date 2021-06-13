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
        ll sum, mx, lmx, rmx;
    };
    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void build()
    {
        for(int i = stLeaf; i >= 0; --i) {
            t[stLeaf + i] = { 0, 0, 0, 0 };
            t[i] = { 0, 0, 0, 0 };
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node].mx;
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, ll v)
    {
        int node = stLeaf + l;
        t[node].sum += v;
        t[node].mx += v;
        t[node].lmx += v;
        t[node].rmx += v;

        node /= 2;
        while(node > 0) {
            Node& cur = t[node];
            Node& left = t[node * 2];
            Node& right = t[node * 2 + 1];

            cur.sum = left.sum + right.sum;
            cur.lmx = max(left.lmx, left.sum + right.lmx);
            cur.rmx = max(right.rmx, right.sum + left.rmx);
            cur.mx = left.rmx + right.lmx;
            cur.mx = max(cur.mx, left.mx);
            cur.mx = max(cur.mx, right.mx);

            node /= 2;
        }
    }
};

struct Point
{
    int x, y;
    ll w;
};
int n;
Point d[3001];
SegTree<3001> sg;

vector<int> xx, yy;
vector<pair<int, ll>> p[3001];
int getx(int x)
{
    return lower_bound(xx.begin(), xx.end(), x) - xx.begin();
}
int gety(int y)
{
    return lower_bound(yy.begin(), yy.end(), y) - yy.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y >> d[i].w;
        xx.push_back(d[i].x);
        yy.push_back(d[i].y);
    }
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());
    xx.erase(unique(xx.begin(), xx.end()), xx.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for(int i = 0; i < n; ++i) {
        d[i].x = getx(d[i].x);
        d[i].y = gety(d[i].y);
    }
    sort(d, d + n, [](const Point& l, const Point& r) {
        if(l.x == r.x) return l.y < r.y;
        return l.x < r.x;
    });
    for(int i = 0; i < n; ++i) {
        p[d[i].x].push_back({ d[i].y, d[i].w });
    }

    sg.init(yy.size());
    ll res = 0;
    for(int i = 0; i < xx.size(); ++i) {
        sg.build();
        for(int j = 0; j < p[i].size(); ++j) {
            sg.add(p[i][j].first, p[i][j].second);
        }
        res = max(res, sg.t[1].mx);

        for(int j = i + 1; j < xx.size(); ++j) {
            for(int k = 0; k < p[j].size(); ++k) {
                sg.add(p[j][k].first, p[j][k].second);
            }
            res = max(res, sg.t[1].mx);
        }
    }

    cout << res;

    return 0;
}
