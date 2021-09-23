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

    void initv(int idx, int v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = max(t[i * 2], t[i * 2 + 1]);
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return 0;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return max(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int idx, int v)
    {
        int node = stLeaf + idx;
        if(t[node] >= v) return;
        t[node] = v;
        node /= 2;
        while(node > 0) {
            t[node] = max(t[node * 2], t[node * 2 + 1]);
            node /= 2;
        }
    }
};

struct Node
{
    int y, tmp;
};

int n, m, p, k;
vector<Node> l2r[100001], r2l[100001];
ll dp[100001][2];
SegTree<100011> sg, sg2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> p >> k;
    for(int i = 0; i < p; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b = m - b;
        if(c == 1) {
            l2r[a + 1].push_back({ b, 0 });
        } else {
            r2l[a].push_back({ b, 0 });
        }
    }

    sg.init(m + 1);
    int mx = 0;
    for(int i = 0; i < n; ++i) {
        for(auto& e : l2r[i]) {
            e.tmp = sg.find(0, e.y) + 1;
            mx = max(mx, e.tmp);
        }
        dp[i][0] = i - mx;
        for(auto& e : l2r[i]) {
            sg.update(e.y, e.tmp);
        }
    }

    sg2.init(m + 1);
    mx = 0;
    for(int i = n - 1; i >= 0; --i) {
        for(auto& e : r2l[i]) {
            e.tmp = sg2.find(0, e.y) + 1;
            mx = max(mx, e.tmp);
        }
        dp[i][1] = n - 1 - i - mx;
        for(auto& e : r2l[i]) {
            sg2.update(e.y, e.tmp);
        }
    }

    int res = 0;
    int l = 0, r = 0, cnt = 0;
    while(l < n) {
        while(r < n && dp[l][1] + dp[r][0] <= k) {
            if(dp[r][0] == 0 && dp[r][1] == 0) cnt++;
            r++;
        }
        res = max(res, r - l - cnt);

        if(dp[l][0] == 0 && dp[l][1] == 0) cnt--;
        l++;
    }

    cout << res;

    return 0;
}
