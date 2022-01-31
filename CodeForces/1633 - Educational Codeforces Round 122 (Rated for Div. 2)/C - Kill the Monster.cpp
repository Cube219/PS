#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Node
    {
        ll h, d;
    };
    Node p, m;
    ll coin, dup, hup;

    cin >> p.h >> p.d;
    cin >> m.h >> m.d;
    cin >> coin >> dup >> hup;

    for(ll i = 0; i <= coin; ++i) {
        ll pturn2 = m.h / (p.d + i * dup);
        if(m.h % (p.d + i * dup) != 0) pturn2++;
        ll mturn2 = (p.h + (coin - i) * hup) / m.d;
        if((p.h + (coin - i) * hup) % m.d != 0) mturn2++;
        if(pturn2 <= mturn2) {
            cout << "YES\n";
            return;
        }
    }
    
    cout << "NO\n";
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
