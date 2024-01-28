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
    int n;
    cin >> n;
    struct Node
    {
        int num, a, b, c, d;
    };
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.num >> v.a >> v.b >> v.c >> v.d;
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.a == r.a) return l.num < r.num;
        return l.a > r.a;
    });
    cout << d[0].num << " ";
    d[0].b = d[0].c = d[0].d = -1;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.b == r.b) return l.num < r.num;
        return l.b > r.b;
    });
    cout << d[0].num << " ";
    d[0].c = d[0].d = -1;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.c == r.c) return l.num < r.num;
        return l.c > r.c;
    });
    cout << d[0].num << " ";
    d[0].d = -1;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.d == r.d) return l.num < r.num;
        return l.d > r.d;
    });
    cout << d[0].num;
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
