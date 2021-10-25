#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

template <int N>
class SegTree
{
public:
    struct Node
    {
        int v, idx;
    };

    Node t[N * 4];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { INF, -1 };
        }
        t[stLeaf] = { 0, -1 };
        for(int i = stLeaf - 1; i >= 1; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node merge(Node l, Node r)
    {
        if(l.v < r.v) return l;
        else return r;
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return { INF, -1 };
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    Node find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx, int v)
    {
        int node = stLeaf + idx;

        t[node].v = v;
        t[node].idx = idx;
        node /= 2;
        while(node > 0) {
            t[node] = merge(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

struct Node
{
    int idx;
    int a, b;
    int top;
    bool operator<(const Node& rhs) const
    {
        return top < rhs.top;
    }
};

int n, a[300011], b[300011];
Node d[300011];
int dp[300011], nxt[300011], rec[300011];
SegTree<300015> sg;
vector<int> delay[300011];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i].a;
        a[i] = d[i].a;
        d[i].idx = i;
        d[i].top = i - d[i].a;
    }
    for(int i = 1; i <= n; ++i) {
        cin >> d[i].b;
        b[i] = d[i].b;
        delay[i + d[i].b].push_back(i);
    }
    sort(d + 1, d + 1 + n, [](const Node& l, const Node& r) {
        if(l.top == r.top) return l.idx < r.idx;
        return l.top < r.top;
    });

    sg.init(n + 1);
    for(int i = 1; i <= n; ++i) {
        Node cur = d[i];
        if(cur.top <= 0) {
            dp[cur.idx] = 1;
            rec[cur.idx] = 0;
            nxt[cur.idx] = 0;
        } else {
            auto res = sg.find(cur.top, cur.idx);

            if(res.idx == -1 || res.v == INF) {
                dp[cur.idx] = INF;
                nxt[cur.idx] = -1;
            } else {
                dp[cur.idx] = res.v + 1;
                rec[cur.idx] = res.idx;
                nxt[cur.idx] = res.idx + b[res.idx];
            }
        }

        for(int idx2 : delay[cur.idx]) {
            sg.add(idx2, dp[cur.idx]);
        }
    }

    if(dp[n] == INF) {
        cout << "-1";
    } else {
        cout << dp[n] << "\n";
        int cur = n;
        do {
            cout << rec[cur] << " ";
            cur = nxt[cur];
        } while(cur > 0);
    }

    return 0;
}
