#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), aa;
    for (auto& v : a) {
        cin >> v;
        aa.push_back(v);
    }
    sort(aa.begin(), aa.end());
    aa.erase(unique(aa.begin(), aa.end()), aa.end());
    for (auto& v : a) v = lower_bound(aa.begin(), aa.end(), v) - aa.begin();

    vector<int> idx(n);
    for (int i = 0; i < n; ++i) {
        idx[a[i]] = i;
    }

    ll res = 0;
    set<int> s;
    for (int i = 0; i < n; ++i) {
        int cur = idx[i];
        auto it = s.insert(cur).first;

        auto lIt = it;
        int lNum = 0;
        auto rIt = it;
        int rNum = 0;
        while (lNum + rNum < k - 1 && next(rIt) != s.end()) {
            rNum++;
            rIt = next(rIt);
        }

        while (rNum >= 0) {
            while (lNum + rNum < k - 1 && lIt != s.begin()) {
                lNum++;
                lIt = prev(lIt);
            }
            if (lNum + rNum < k - 1) break;

            int prevL = -1;
            if (lIt != s.begin()) {
                prevL = *prev(lIt);
            }
            int nextR = n;
            if (next(rIt) != s.end()) {
                nextR = *next(rIt);
            }
            res += (ll)aa[i] * (*lIt - prevL) * (nextR - *rIt);

            rIt = prev(rIt);
            rNum--;
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
