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

template <int N>
struct SegTree
{
    struct Node
    {
        ll mx, lmx, rmx, sum;
    };
    Node t[N * 2 + 1];
    int n;

    void init(int _n)
    {
        n = _n;

        for(int i = 0; i < n; ++i) {
            t[i + n] = { 0, 0, 0, 0 };
        }
        for(int i = n - 1; i >= 1; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node merge(Node l, Node r)
    {
        Node res;
        res.mx = max(l.mx, r.mx);
        res.mx = max(res.mx, l.rmx + r.lmx);
        res.lmx = max(l.lmx, l.sum + r.lmx);
        res.rmx = max(r.rmx, l.rmx + r.sum);
        res.sum = l.sum + r.sum;

        return res;
    }

    Node find(int l, int r)
    {
        l += n;
        r += n + 1;
        Node resl = { 0, 0, 0, 0 };
        Node resr = { 0, 0, 0, 0 };
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    void update(int idx, ll v)
    {
        idx += n;
        t[idx].mx += v;
        t[idx].lmx += v;
        t[idx].rmx += v;
        t[idx].sum += v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }
};

struct Node
{
    int x, y;
    bool s;
};

int n, m;
ll c1, c2;
vector<int> xx, yy;
vector<Node> d;
SegTree<2005> sg;
vector<Node> d2[2001];

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
        int x, y;
        cin >> x >> y;
        d.push_back({ x, y, true });
        xx.push_back(x);
        yy.push_back(y);
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        d.push_back({ x, y, false });
        xx.push_back(x);
        yy.push_back(y);
    }
    cin >> c1 >> c2;

    sort(xx.begin(), xx.end());
    xx.erase(unique(xx.begin(), xx.end()), xx.end());
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for(int i = 0; i < n + m; ++i) {
        d[i].x = getx(d[i].x);
        d[i].y = gety(d[i].y);
    }
    for(int i = 0; i < n + m; ++i) {
        d2[d[i].x].push_back(d[i]);
    }

    ll res = 0;
    for(int i = 0; i < xx.size(); ++i) {
        sg.init(yy.size());
        for(int j = i; j < xx.size(); ++j) {
            for(auto& p : d2[j]) {
                ll v;
                if(p.s == true) v = c1;
                else v = -c2;
                sg.update(p.y, v);
            }

            res = max(res, sg.find(0, yy.size() - 1).mx);
        }
    }

    cout << res;

    return 0;
}
