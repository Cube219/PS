#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#undef _LIBCPP_ENABLE_ASSERTIONS


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
        ll a, b, c, p;
    };
    vector<Node> d(n);
    for (auto& v : d) {
        cin>>v.a>>v.b>>v.c>>v.p;
    }

    bool res = true;
    ll curA = 0, curB = 0, curC = 0, curP = 0;
    for (auto [a, b, c, p] : d) {
        ll reqA = max(0ll, a - curA);
        ll reqB = max(0ll, b - curB);
        ll reqC = max(0ll, c - curC);

        ll reqP = reqA + reqB + reqC + 1;
        if (curP + reqP > p) {
            res = false;
            break;
        }

        curA += reqA;
        curB += reqB;
        curC += reqC;
        curP += reqP;
    }

    cout << (res ? "YES" : "NO") << "\n";
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
