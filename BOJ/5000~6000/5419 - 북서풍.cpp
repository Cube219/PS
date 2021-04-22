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
    int t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = 0;
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = 0;
        }
    }
    void clear()
    {
        for(int i = stLeaf * 2; i > 0; --i) {
            t[i] = 0;
        }
    }
    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l)
    {
        int node = stLeaf + l;
        t[node]++;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

struct Point
{
    int x, y;
};

int tNum;
int n;
Point p[75001];
SegTree<75001> sg;
vector<int> yidx;
ll res;

int getidx(int y)
{
    return lower_bound(yidx.begin(), yidx.end(), y) - yidx.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) { 
        cin >> n;
        yidx.clear();
        res = 0;
        for(int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            p[i] = { a, b };
            yidx.push_back(b);
        }
        sort(p, p + n, [](const Point& l, const Point& r) {
            if(l.x == r.x) return l.y > r.y;
            return l.x < r.x;
        });
        sort(yidx.begin(), yidx.end());
        yidx.erase(unique(yidx.begin(), yidx.end()), yidx.end());

        sg.init(yidx.size());

        for(int i = 0; i < n; ++i) {
            int idx = getidx(p[i].y);
            res += sg.find(idx, yidx.size() - 1);
            sg.add(idx);
        }

        cout << res << "\n";
    }

    return 0;
}
