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
    int cm, kg;
    cin >> cm >> kg;

    double c = (double)cm / 100;

    double bmi = (double)kg / (c * c);

    if(cm <= 140) {
        cout << "6\n";
    } else if(cm < 146) {
        cout << "5\n";
    } else if(cm < 159) {
        cout << "4\n";
    } else if(cm < 161) {
        if(16.0 <= bmi && bmi < 35) cout << "3\n";
        else cout << "4\n";
    } else if(cm < 204) {
        if(20 <= bmi && bmi < 25) cout << "1\n";
        else if(18.5 <= bmi && bmi < 30) cout << "2\n";
        else if(16 <= bmi && bmi < 35) cout << "3\n";
        else cout << "4\n";
    } else {
        cout << "4\n";
    }
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
