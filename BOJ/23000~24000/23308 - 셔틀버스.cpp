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
    int n, m;
    cin >> n >> m;
    vector<int> dis(n - 1);
    for(auto& v : dis) cin >> v;
    vector<int> cnt(n, 0);
    for(int i = 0; i < m; ++i) {
        int v; cin >> v; v--;
        cnt[v]++;
    }

    int cycle = INF;
    for(int i = 1; i < n - 1; ++i) {
        cycle = min(cycle, cnt[i]);
    }
    cycle = min(cycle / 2, min(cnt[0], cnt[n - 1]));

    for(int i = 1; i < n - 1; ++i) {
        cnt[i] -= cycle * 2;
    }
    cnt[0] -= cycle;
    cnt[n - 1] -= cycle;

    int cntSum = 0;
    for(int i = 0; i < n; ++i) {
        if(cnt[i] != 0 && cnt[i] != 1 && cnt[i] != 2) {
            cout << "F";
            return;
        }
        cntSum += cnt[i];
    }

    ll res = LNF;

    ll disSum = accumulate(dis.begin(), dis.end(), 0);

    if(cntSum > 0) {
        auto L = [&]() {
            int cur = cntSum;
            ll v = 0;

            int i = 0;
            for(; i < n && cnt[i] == 0; ++i) {
            }
            i++;
            cur--;
            for(; i < n && cnt[i] > 0; ++i) {
                cur--;
                v += dis[i - 1];
            }

            if(cur != 0) return;
            v += cycle * disSum * 2;
            res = min(res, v);
        };
        auto LR = [&]() {
            int cur = cntSum - 1;
            ll v = 0;

            if(cnt[0] != 1) return;
            int i = 1;
            for(; i < n && cnt[i] == 2; ++i) {
                cur -= 2;
                v += dis[i - 1] * 2;
            }
            for(; i < n && cnt[i] == 1; ++i) {
                cur--;
                v += dis[i - 1];
            }

            if(cur != 0) return;
            v += cycle * disSum * 2;
            res = min(res, v);
        };
        auto LRL = [&]() {
            if(cnt[0] != 1 || cnt[n - 1] != 1) return;
            ll v = disSum;
            int cur = cntSum - n;

            for(int i = 1; i < n && cnt[i] == 2; ++i) {
                v += dis[i - 1];
                cur--;
            }
            for(int i = n - 2; i >= 0 && cnt[i] == 2; --i) {
                v += dis[i];
                cur--;
            }

            if(cur != 0) return;
            v += cycle * disSum * 2;
            res = min(res, v);
        };

        L();
        LR();
        LRL();

        reverse(cnt.begin(), cnt.end());
        reverse(dis.begin(), dis.end());

        L();
        LR();
        LRL();
    } else if(cntSum == 0) {
        int mx = 0;
        for(int i = 0; i < n - 1; ++i) {
            mx = max(mx, dis[i]);
        }
        res = cycle * disSum * 2 - mx;
    }

    if(res == LNF) cout << "F";
    else cout << res;
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
