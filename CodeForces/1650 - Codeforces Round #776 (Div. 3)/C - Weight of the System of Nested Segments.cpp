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
    struct Node
    {
        int pos, w, idx;
    };
    vector<Node> d(m);
    for(int i = 0; i < m; ++i) {
        cin >> d[i].pos >> d[i].w;
        d[i].idx = i;
    }

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.w < r.w;
    });

    vector<Node> res;
    for(int i = 0; i < n * 2; ++i) {
        res.push_back(d[i]);
    }
    sort(res.begin(), res.end(), [](const Node& l, const Node& r) {
        return l.pos < r.pos;
    });

    ll sum = 0;
    vector<pair<int, int>> pr;
    for(int i = 0; i < n; ++i) {
        sum += res[i].w + res[n * 2 - 1 - i].w;
        pr.push_back({ res[i].idx, res[n * 2 - 1 - i].idx });
    }

    cout << sum << "\n";
    for(auto [l, r] : pr) cout << l + 1 << " " << r + 1 << "\n";
    cout << "\n";
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
