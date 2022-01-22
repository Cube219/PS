#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    struct Node
    {
        int a, b;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.a;
    for(auto& v : d) cin >> v.b;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.a == r.a) return l.b > r.b;
        return l.a < r.a;
    });

    for(auto& cur : d) {
        if(k < cur.a) break;
        k += cur.b;
    }

    cout << k << "\n";
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
