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
    int t[N * 3], cnt[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void addImpl(int cl, int cr, int l, int r, int node, int v)
    {
        if(l <= cl && cr <= r) {
            t[node] += v;
        } else if(cr < l || r < cl) return;
        else {
            int m = (cl + cr) / 2;
            addImpl(cl, m, l, r, node * 2, v);
            addImpl(m + 1, cr, l, r, node * 2 + 1, v);
        }
        if(t[node] > 0) cnt[node] = cr - cl + 1;
        else {
            if(node >= stLeaf) cnt[node] = 0;
            else cnt[node] = cnt[node * 2] + cnt[node * 2 + 1];
        }
    }

    int find()
    {
        return cnt[1];
    }

    void add(int l, int r, int v)
    {
        addImpl(0, stLeaf - 1, l, r, 1, v);
    }
};

SegTree<30001> sg;

struct Node
{
    int x;
    int y1, y2;
    bool isend;
};

int n;
Node d[200001];
int maxy;
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
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        d[i * 2] = { x1, y1, y2, false };
        d[i * 2 + 1] = { x2, y1, y2, true };
        maxy = max(maxy, y2);
    }
    sort(d, d + n * 2, [](const Node& l, const Node& r) {
        return l.x < r.x;
    });

    sg.init(maxy + 1);
    int lastx = d[0].x;
    for(int i = 0; i < n * 2; ++i) {
        int cnt = sg.find();
        res += cnt * (d[i].x - lastx);
        lastx = d[i].x;
        if(d[i].isend == false) {
            sg.add(d[i].y1, d[i].y2 - 1, 1);
        } else {
            sg.add(d[i].y1, d[i].y2 - 1, -1);
        }
    }

    cout << res;

    return 0;
}
