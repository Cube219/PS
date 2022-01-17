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
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    sort(d.begin(), d.end());
    vector<pair<int, int>> d2;
    for(int i = 0; i < n; ++i) {
        if(d2.size() == 0 || d2.back().first != d[i]) d2.push_back({ d[i], 0 });
        d2.back().second++;
    }

    auto get = [](int v) {
        int k = 1;
        while(k < v) k *= 2;
        return k - v;
    };

    int res = INF;
    for(int r1 = 0; r1 <= n; r1 == 0 ? r1++ : r1 *= 2) {
        for(int r2 = 0; r2 <= n; r2 == 0 ? r2 ++ : r2 *= 2) {
            int cur = 0, i = 0, cnt = 0;
            for(i = 0; i < d2.size(); ++i) {
                if(cnt + d2[i].second > r1) {
                    break;
                }
                cnt += d2[i].second;
            }
            cur += get(cnt);
            cnt = 0;
            for(; i < d2.size(); ++i) {
                if(cnt + d2[i].second > r2) {
                    break;
                }
                cnt += d2[i].second;
            }
            cur += get(cnt);
            cnt = 0;
            for(; i < d2.size(); ++i) {
                cnt += d2[i].second;
            }
            cur += get(cnt);

            res = min(res, cur);

        }
    }

    cout << res << "\n";
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
