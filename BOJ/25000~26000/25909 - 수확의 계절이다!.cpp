#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <unordered_map>
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
    struct Move { char dir; int len; };
    vector<Move> d(n);
    for(auto& v : d) cin >> v.dir >> v.len;

    map<pair<int, int>, int> mp;
    vector<vector<int>> tList;
    int cx = 0, cy = 0, t = 0;
    for(auto [dir, len] : d) {
        int dx = 0, dy = 0;
        if(dir == 'E') dx = 1;
        else if(dir == 'W') dx = -1;
        else if(dir == 'S') dy = -1;
        else dy = 1;

        for(int i = 0; i < len; ++i) {
            cx += dx;
            cy += dy;
            t++;

            auto it = mp.find({ cx, cy });
            if(it == mp.end()) {
                it = mp.insert({ { cx, cy }, (int)tList.size() }).first;
                tList.emplace_back();
            }

            tList[it->second].push_back(t);
        }
    }

    auto ck = [&](int x) {
        int cnt = 0;
        for(auto& tl : tList) {
            int lastTime = tl[0];
            for(int time : tl) {
                if(time - lastTime >= x) {
                    cnt++;
                    lastTime = time;
                }
            }
        }

        return cnt >= k;
    };

    int lo = 0, hi = 1000001;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ck(mid)) lo = mid;
        else hi = mid;
    }
    if(lo == 0) lo = -1;
    cout << lo;
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
