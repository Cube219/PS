#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

vector<int> mst[1050001];
int stLeaf;

void init()
{
    for(int i = stLeaf - 1; i > 0; --i) {
        auto& cur = mst[i];
        auto& left = mst[i * 2];
        auto& right = mst[i * 2 + 1];

        cur.clear();
        auto lit = left.begin();
        auto rit = right.begin();
        while(lit != left.end() && rit != right.end()) {
            if(*lit < *rit) {
                cur.push_back(*lit);
                ++lit;
            } else {
                cur.push_back(*rit);
                ++rit;
            }
        }
        cur.insert(cur.end(), lit, left.end());
        cur.insert(cur.end(), rit, right.end());
    }
}

int query(int cl, int cr, int l, int r, int node, int k)
{
    if(cr < l || r < cl) return 0;
    else if(l <= cl && cr <= r) {
        return mst[node].end() - upper_bound(mst[node].begin(), mst[node].end(), k);
    }
    int m = (cl + cr) / 2;
    return query(cl, m, l, r, node * 2, k) + query(m + 1, cr, l, r, node * 2 + 1, k);
}

// (a / b) % mod == (a * b^(mod-2)) % mod
ll divmod(ll a, ll b, ll mod)
{
    ll res = 1;
    ll ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}

int n, q, rt;
vector<int> g[300001];
int a[300001], w[300001], a2[300001];
int st[300001], ed[300001], cnt;
ll res[300001];

void dfs(int cur)
{
    st[cur] = cnt;
    a2[cnt] = a[cur];
    cnt++;
    for(int nxt : g[cur]) {
        dfs(nxt);
    }
    ed[cur] = cnt - 1;
}

ll dfs2(int cur)
{
    ll ret;
    int num = ed[cur] - st[cur] + 1;
    int negnum = query(0, stLeaf - 1, st[cur] + 1, ed[cur], 1, a[cur] + w[cur]);
    ret = (ll)(num - negnum) * divmod(1, num, MOD) % MOD;
    for(int nxt : g[cur]) {
        ret += dfs2(nxt);
        ret %= MOD;
    }
    res[cur] = ret;
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        if(p != -1) g[p].push_back(i);
        else rt = i;
    }
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    dfs(rt);

    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        mst[stLeaf + i].push_back(a2[i]);
    }
    init();

    dfs2(rt);

    for(int i = 0; i < q; ++i) {
        int aa;
        cin >> aa;
        cout << res[aa - 1] << "\n";
    }

    return 0;
}
