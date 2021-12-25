#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    string str;
    cin >> str;

    vector<ll> d(str.size());
    for(int i = 0; i < str.size(); ++i) {
        d[i] = str[i] - '0';
        if(i > 0) d[i] += d[i - 1];
    }
    vector<ll> res;
    for(int i = str.size() - 1; i >= 1; --i) {
        res.push_back(d[i] % 10);
        d[i] /= 10;
        int idx = 1;
        while(d[i] > 0) {
            if(i - idx == 0) {
                d[i - idx] += d[i];
                break;
            }
            d[i - idx] += d[i] % 10;
            d[i] /= 10;
            idx++;
        }
    }
    res.push_back(d[0]);
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
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
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
