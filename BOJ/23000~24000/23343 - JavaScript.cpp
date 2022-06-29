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
    string a, b;
    cin >> a >> b;

    ll aa = 0, bb = 0;
    for(char ch : a) {
        if(ch < '0' || '9' < ch) {
            cout << "NaN";
            return;
        }
        aa *= 10;
        aa += ch - '0';
    }

    for(char ch : b) {
        if(ch < '0' || '9' < ch) {
            cout << "NaN";
            return;
        }
        bb *= 10;
        bb += ch - '0';
    }

    cout << aa - bb;
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
