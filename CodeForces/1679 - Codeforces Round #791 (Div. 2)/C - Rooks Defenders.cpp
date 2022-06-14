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

struct Fenwick
{
    int n;
    vector<ll> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, ll dv)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        pos++;
        ll res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> row(n, 0), col(n, 0);
    Fenwick rsg(n), csg(n);
    for(int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, y;
            cin >> x >> y;
            if(row[x - 1] == 0) rsg.update(x - 1, 1);
            row[x - 1]++;
            if(col[y - 1] == 0) csg.update(y - 1, 1);
            col[y - 1]++;
        } else if(t == 2) {
            int x, y;
            cin >> x >> y;
            row[x - 1]--;
            col[y - 1]--;

            if(row[x - 1] == 0) rsg.update(x - 1, -1);
            if(col[y - 1] == 0) csg.update(y - 1, -1);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;

            bool res = false;
            ll rcnt = rsg.query(x2);
            if(x1 > 0) rcnt -= rsg.query(x1 - 1);
            ll ccnt = csg.query(y2);
            if(y1 > 0) ccnt -= csg.query(y1 - 1);

            if(rcnt == (x2-x1+1) || ccnt == (y2-y1+1)) {
                res = true;
            }

            if(res) cout << "Yes\n";
            else cout << "No\n";
        }
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
