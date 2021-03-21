#define _CRT_SECURE_NO_WARNINGS 1

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

    void init(int n, int* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            if(pData == nullptr) t[stLeaf + i] = 0;
            else t[stLeaf + i] = pData[i];
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = max(t[i * 2], t[i * 2 + 1]);
        }
    }

    void propagate(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += lazy[node];
        lazy[node] = 0;
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        propagate(cl, cr, node);
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            propagate(cl, cr, node);
            return;
        } else if(cr < l || r < cl) return;
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2, v);
        addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = max(t[node * 2], t[node * 2 + 1]);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

struct Area
{
    int y1;
    int y2;
};

int n;
Area d[100001], d2[100001];
SegTree<200000> sg;
vector<int> idx;

int getIdx(int y)
{
    return lower_bound(idx.begin(), idx.end(), y) - idx.begin();
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sg.init(n * 2 + 1, nullptr);
    for(int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        d[i].y1 = y2;
        d[i].y2 = y1;
        idx.push_back(y1);
        idx.push_back(y2);
        d2[i] = d[i];
    }
    sort(idx.begin(), idx.end());
    idx.erase(unique(idx.begin(), idx.end()), idx.end());
    sort(d, d + n, [](Area& l, Area& r) {
        return l.y1 < r.y1;
    });
    d[n].y1 = 10000005;
    sort(d2, d2 + n, [](Area& l, Area& r) {
        return l.y2 < r.y2;
    });
    d2[n].y2 = 10000005;

    for(int i = 0; i < n; ++i) {
        int y1Idx = getIdx(d[i].y1);
        int y2Idx = getIdx(d[i].y2);
        sg.add(y1Idx, y2Idx, 1);
    }

    int d1Idx = 0, d2Idx = 0;
    int res = 0;
    int r1 = 0;
    for(int i = 0; i < idx.size(); ++i) {
        int yLine = idx[i];
        while(d[d1Idx].y1 <= yLine) {
            r1++;
            int y1Idx = getIdx(d[d1Idx].y1);
            int y2Idx = getIdx(d[d1Idx].y2);
            sg.add(y1Idx, y2Idx, -1);
            d1Idx++;
        }
        while(d2[d2Idx].y2 < yLine) {
            r1--;
            int y1Idx = getIdx(d2[d2Idx].y1);
            int y2Idx = getIdx(d2[d2Idx].y2);
            sg.add(y1Idx, y2Idx, 1);
            d2Idx++;
        }
        int r2 = sg.t[1];
        if(res < r1 + r2) {
            res = r1 + r2;
        }
    }

    cout << res;

    return 0;
}
