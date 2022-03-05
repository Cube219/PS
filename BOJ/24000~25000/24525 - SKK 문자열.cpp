#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
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
    int n = str.size();

    vector<int> d(n), num(n, 0);
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'S') {
            d[i] = -2;
            num[i]++;
        } else if(str[i] == 'K') {
            d[i] = 1;
            num[i]++;
        } else {
            d[i] = 0;
        }
    }
    for(int i = 1; i < n; ++i) {
        d[i] += d[i - 1];
        num[i] += num[i - 1];
    }

    int res = -1;
    map<int, int> minIdx;
    for(int i = 0; i < n; ++i) {
        if(d[i] == 0) {
            if(num[i] > 0) res = max(res, i + 1);
        } else {
            auto it = minIdx.find(d[i]);
            if(it != minIdx.end()) {
                int l = it->second;
                if(num[i] - num[l] > 0) res = max(res, i - l);
            } else {
                minIdx.insert({ d[i], i });
            }
        }
    }

    cout << res;
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
