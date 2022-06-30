#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        int g, s, b;
        string str;
    };
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.g >> v.s >> v.b;
        getline(cin, v.str);
        v.str = v.str.substr(1);
    }

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return (tie(l.g, l.s, l.b) > tie(r.g, r.s, r.b));
    });

    cout << d[0].str;
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
