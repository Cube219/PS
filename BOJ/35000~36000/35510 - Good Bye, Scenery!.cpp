#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#undef _LIBCPP_ENABLE_ASSERTIONS


#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <cassert>
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
        for(pos++; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        ll res = 0;
        for(pos++; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v : a) {
        cin >> v;
        v--;
    }
    vector<vector<int>> idx(n);
    for(int i = 0; i < n; ++i) {
        idx[a[i]].push_back(i);
    }

    ll res = 0;
    set<int> candi;
    Fenwick fw(n);
    for(int i = 0; i < n; ++i) {
        fw.update(i, 1);
    }
    for(int i = n - 1; i >= 0; --i) {
        for (int v : idx[i]) candi.insert(v);

        if (candi.empty()) {
            res = -1;
            break;
        }
        auto lastIt = candi.end();
        --lastIt;

        int revIdx = n - * lastIt - 1;
        res += fw.query(revIdx) - 1;
        fw.update(revIdx, -1);
        candi.erase(lastIt);
    }

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
