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
    string s, t;
    cin >> s >> t;

    vector<ll> d(t.size(), 0);
    for(int i = 0; i < s.size(); ++i) {
        for(int j = 0; j < t.size(); ++j) {
            if(s[i] == t[j]) {
                if(j == 0) d[0]++;
                else if(d[j - 1] > 0) {
                    d[j - 1]--;
                    d[j]++;
                }
            }
        }
    }

    cout << d[(int)t.size() - 1];
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
