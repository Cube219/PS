#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, c;
    ll k;
    cin >> n >> c >> k;
    string str;
    cin >> str;
    struct Query
    {
        int type, i, j;
    };
    vector<Query> ql(c);
    for(auto& q : ql) {
        char ch; cin >> ch;
        q.type = ch == 'S' ? 0 : 1;
        cin >> q.i >> q.j;
    }

    ll cycle = k / c;
    k %= c;
    struct Node { int idx, cnt; };
    auto mul = [&](vector<Node>& l, vector<Node>& r) {
        vector<Node> res(n);
        for(int i = 0; i < n; ++i) {
            res[i].idx = l[r[i].idx].idx;
            res[i].cnt = (l[r[i].idx].cnt + r[i].cnt) % 26;
        }

        return res;
    };
    vector<Node> cur(n);
    for(int i = 0; i < n; ++i) {
        cur[i].idx = i;
        cur[i].cnt = 0;
    }

    // cycle 1
    vector<Node> d = cur;
    for(auto& q : ql) {
        if(q.type == 0) swap(d[q.i], d[q.j]);
        else d[q.i].cnt = (d[q.i].cnt + q.j) % 26;
    }
    for(; cycle > 0; cycle >>= 1) {
        if(cycle & 1) cur = mul(cur, d);
        d = mul(d, d);
    }
    // remain
    for(int i = 0; i < k; ++i) {
        auto& q = ql[i];
        if(q.type == 0) swap(cur[q.i], cur[q.j]);
        else cur[q.i].cnt = (cur[q.i].cnt + q.j) % 26;
    }

    for(int i = 0; i < n; ++i) {
        int v = (str[cur[i].idx] - 'A' + cur[i].cnt) % 26;
        cout << (char)(v + 'A');
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
