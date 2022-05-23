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
    double sum = 0.0;
    int cnt = 0;
    for(int i = 0; i < 20; ++i) {
        string a; double b; string c;
        cin >> a >> b >> c;
        cnt += b;
        if(c == "A+") {
            sum += 4.5 * b;
        } else if(c == "A0") {
            sum += 4.0 * b;
        } else if(c == "B+") {
            sum += 3.5 * b;
        } else if(c == "B0") {
            sum += 3.0 * b;
        } else if(c == "C+") {
            sum += 2.5 * b;
        } else if(c == "C0") {
            sum += 2.0 * b;
        } else if(c == "D+") {
            sum += 1.5 * b;
        } else if(c == "D0") {
            sum += 1.0 * b;
        } else if(c == "F") {
        } else if(c == "P") {
            cnt -= b;
        }
    }

    cout << fixed << setprecision(8) << sum / cnt;
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
