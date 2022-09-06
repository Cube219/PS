#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> ga(n), gb(n), w(n);
    for(auto& v : ga) cin >> v;
    for(auto& v : gb) cin >> v;
    for(auto& v : w) cin >> v;

    double hi = INF;
    for(int i = 0; i < n; ++i) {
        hi = min(hi, (double)w[i] / ga[i]);
    }

    auto cal = [&](double a) {
        double b = INF;
        for(int i = 0; i < n; ++i) {
            double remain = (double)w[i] - a * ga[i];
            b = min(b, remain / gb[i]);
        }

        return a * x + b * y;
    };

    double lo = 0;
    while(hi - lo > 1e-10) {
        double p = (lo * 2 + hi) / 3;
        double q = (lo + hi * 2) / 3;

        if(cal(p) <= cal(q)) lo = p;
        else hi = q;
    }

    double a = lo;
    double b = INF;
    for(int i = 0; i < n; ++i) {
        double remain = (double)w[i] - a * ga[i];
        b = min(b, remain / gb[i]);
    }
    cout << fixed << setprecision(2);
    cout << a * x + b * y << "\n";
    cout << a << " " << b;
}

int main()
{
#ifdef CUBE_PS
    freopen("input2.txt", "r", stdin);
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
