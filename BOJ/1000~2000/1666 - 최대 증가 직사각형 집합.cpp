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


struct Node
{
    int x1, y1, x2, y2;
};
struct Line
{
    int x, y, idx;
    int isRight;
};

int n;
Node d[100001];
Line d2[200001];
int num[100001];
int res;
SegTree<100002> sg;

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
        d2[i * 2] = { x1, y1, i, 0 };
        d2[i * 2 + 1] = { x2, y2, i, 1 };
    }
    sort(d2, d2 + n * 2, [](const Line& l, const Line& r) {
        if(l.x == r.x) {
            return l.isRight < r.isRight;
        }
        return l.x < r.x;
    });

    sg.init(100001);

    for(int i = 0; i < n * 2; ++i) {
        if(d2[i].isRight == 0) {
            num[d2[i].idx] = sg.find(0, d2[i].y - 1);
            res = max(res, num[d2[i].idx]);
        } else {
            sg.add(d2[i].y, num[d2[i].idx] + 1);
        }
    }

    cout << res + 1;

    return 0;
}
