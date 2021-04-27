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
    int t[N * 3], lazy[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx, int v)
    {
        int node = stLeaf + idx;
        t[node] = max(t[node], v);
        node /= 2;
        while(node > 0) {
            t[node] = max(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};


struct Point
{
    int x, y;
    int idx;
    bool isend;
};

int n, p;
int value[100001];
Point d[200001];
SegTree<200001> sg;
vector<int> xx, yy;
int res;

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

    cin >> n >> p;
    for(int i = 0; i < p; ++i) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        d[i * 2] = { sx, sy, i, false };
        d[i * 2 + 1] = { ex, ey, i, true };
        value[i] = (ex - sx) + (ey - sy);
        xx.push_back(sx);
        xx.push_back(ex);
        yy.push_back(sy);
        yy.push_back(ey);
    }
    sort(xx.begin(), xx.end());
    xx.erase(unique(xx.begin(), xx.end()), xx.end());
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for(int i = 0; i < p * 2; ++i) {
        d[i].x = getx(d[i].x);
        d[i].y = gety(d[i].y);
    }
    sort(d, d + p * 2, [](const Point& l, const Point& r) {
        if(l.x == r.x) return l.y > r.y;
        return l.x > r.x;
    });
    sg.init(yy.size() + 1);

    for(int i = 0; i < p * 2; ++i) {
        if(d[i].isend == true) {
            int tmp = sg.find(d[i].y, yy.size()) + value[d[i].idx];
            value[d[i].idx] = tmp;
            res = max(res, tmp);
        } else {
            sg.add(d[i].y, value[d[i].idx]);
        }
    }

    cout << n * 2 - res;

    return 0;
}
