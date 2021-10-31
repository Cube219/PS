#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 10000000000000000;

template <int N>
class SegTree_old
{
public:
    ll t[N * 4];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }

    void build()
    {
        for(int i = 1; i < stLeaf * 2; ++i) {
            t[i] = -INF;
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node, int s)
    {
        if(cl == cr) {
            if(t[node] < s) return -INF;
            else return cl;
        }

        if(cr < l || r < cl) return -INF;
        // if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;

        if(m + 1 <= r && t[node * 2 + 1] >= s) {
            ll res = findImpl(m + 1, cr, l, r, node * 2 + 1, s);
            if(res == -INF) {
                return findImpl(cl, m, l, r, node * 2, s);
            }
            return res;
        } else if(t[node * 2] >= s) {
            return findImpl(cl, m, l, r, node * 2, s);
        } else {
            return -INF;
        }
    }

    ll find(ll s, ll u)
    {
        return findImpl(0, stLeaf - 1, 0, u, 1, s);
    }

    void update(int idx, ll v)
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

struct Query
{
    int s, e, idx;
    ll u;
};

struct Node
{
    int s, e;
    ll u;
};

int n, m;
int d[2001];
Query q[200001];
vector<Node> v;
ll res[200001];
SegTree_old<4000001> sg;
vector<ll> u;

ll getu(ll uu)
{
    return lower_bound(u.begin(), u.end(), uu) - u.begin();
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> q[i].s >> q[i].e >> q[i].u;
        q[i].s--; q[i].e--;
        q[i].idx = i;

        u.push_back(q[i].u);
    }
    sort(q, q + m, [](const Query& l, const Query& r) {
        return l.e < r.e;
    });
    for(int i = 0; i < n; ++i) {
        ll sum = 0;
        for(int j = i; j < n; ++j) {
            sum += d[j];
            v.push_back({ i, j, sum });
            u.push_back(sum);
        }
    }
    sort(v.begin(), v.end(), [](const Node& l, const Node& r) {
        return l.e > r.e;
    });

    sort(u.begin(), u.end());
    u.erase(unique(u.begin(), u.end()), u.end());
    for(int i = 0; i < m; ++i) {
        q[i].u = getu(q[i].u);
    }
    for(auto& vv : v) {
        vv.u = getu(vv.u);
    }

    sg.init(u.size());
    sg.build();
    for(int i = 0; i < m; ++i) {
        auto& qq = q[i];
        while(v.size() > 0 && v.back().e <= qq.e) {
            auto& vv = v.back();
            sg.update(vv.u, vv.s);
            v.pop_back();
        }
        ll r = sg.find(qq.s, qq.u);
        if(r < 0) res[qq.idx] = -INF;
        else res[qq.idx] = u[r];
    }

    for(int i = 0; i < m; ++i) {
        if(res[i] == -INF) cout << "NONE\n";
        else cout << res[i] << "\n";
    }

    return 0;
}
