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
    vector<int> d(3);
    for(auto& v : d) cin >> v;
    sort(d.begin(), d.end());
    reverse(d.begin(), d.end());

    int a = d[0];
    int b = d[1];
    int c = d[2];

    int res = 0;
    if(a % 2 == 0) {
        if(b % 2 == 1) {
            if(c < a - b + 1) res = 1;
            else {
                c -= a - b + 1;
                c %= 4;
                switch(c) {
                    case 0: res = 1; break;
                    case 1: res = 1; break;
                    case 2: res = 0; break;
                    case 3: res = 1; break;
                }
            }
        } else {
            if(c < a - b + 1) res = c % 2;
            else {
                c -= a - b + 1;
                c %= 4;
                switch(c) {
                    case 0: res = 1; break;
                    case 1: res = 0; break;
                    case 2: res = 0; break;
                    case 3: res = 0; break;
                }
            }
        }
    } else {
        if(b % 2 == 1) {
            if(a == b && c == 1) res = 0;
            else if(c < a - b + 3) res = 1;
            else {
                c -= a - b + 3;
                c %= 4;
                switch(c) {
                    case 0: res = 1; break;
                    case 1: res = 1; break;
                    case 2: res = 0; break;
                    case 3: res = 1; break;
                }
            }
        } else {
            if(c < a - b + 1) res = c % 2;
            else {
                c -= a - b + 1;
                c %= 4;
                switch(c) {
                    case 0: res = 0; break;
                    case 1: res = 1; break;
                    case 2: res = 1; break;
                    case 3: res = 1; break;
                }
            }
        }
    }

    if(res == 0) cout << "B\n";
    else cout << "R\n";
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
