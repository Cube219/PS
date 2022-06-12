#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<char> isA(n, false);
    for(int i = 0; i < k; ++i) {
        int v;
        cin >> v;
        isA[v - 1] = true;
    }
    struct Node
    {
        int x, y;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.x >> v.y;

    double lo = 0, hi = 400001;
    while(hi - lo > 1e-7) {
        double m = (lo + hi) / 2;
        vector<char> ck(n, false);

        for(int i = 0; i < n; ++i) {
            if(isA[i]) {
                for(int j = 0; j < n; ++j) {
                    ll dx = d[i].x - d[j].x;
                    ll dy = d[i].y - d[j].y;
                    if(sqrt(dx*dx + dy*dy) <= m) {
                        ck[j] = true;
                    }
                }
            }
        }

        bool res = true;
        for(int i = 0; i < n; ++i) {
            if(ck[i] == false) {
                res = false;
                break;
            }
        }
        if(res) hi = m;
        else lo = m;
    }

    cout << fixed << setprecision(15) << hi;
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
