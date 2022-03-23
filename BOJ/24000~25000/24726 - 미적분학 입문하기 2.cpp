#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;
constexpr double PI = 3.1415926535897932;

void solve()
{
    vector<ll> x(3), y(3);
    for(int i = 0; i < 3; ++i) {
        cin >> x[i] >> y[i];
    }

    auto get = [&]() {
        double res = 0;

        for(int i = 0; i < 3; ++i) {
            int j = (i + 1) % 3;
            if(x[j] == x[i]) continue;
            else if(y[j] == y[i]) {
                double r1 = y[i] * y[i] * x[j];
                double r2 = y[i] * y[i] * x[i];
                res += r1 - r2;
                continue;
            }
            double a = (double)(y[j] - y[i]) / (x[j] - x[i]);
            double b = y[i] - x[i] * a;

            double u1 = a * x[j] + b;
            double u2 = a * x[i] + b;
            double u = u1 * u1 * u1 - u2 * u2 * u2;
            res += u / (a * 3);
        }

        return abs(res);
    };

    cout << fixed << setprecision(10);
    cout << get() *  PI << " ";
    for(int i = 0; i < 3; ++i) {
        swap(x[i], y[i]);
    }
    cout << get() * PI;
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
