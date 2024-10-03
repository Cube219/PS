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
    int n, m;
    cin >> n >> m;
    ll v, p, s;
    cin >> v >> p >> s;
    ll vps = v + p + s;
    struct Node
    {
        ll v, p, s, vps;
        int idx;
        bool operator<(const Node& rhs) const {
            return vps > rhs.vps;
        }
    };
    vector<Node> d(n);
    int i = 1;
    for (auto& v : d) {
        cin >> v.v >> v.p >> v.s;
        v.vps = v.v + v.p + v.s;
        v.idx = i;
        i++;
    }

    sort(d.begin(), d.end());
    vector<int> res;
    m--;
    for (int i = 0; i < n && m > 0; ++i) {
        if (d[i].vps > vps) continue;
        m--;
        res.push_back(d[i].idx);
    }

    cout << "0";
    for (int v : res) cout << " " << v;
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
