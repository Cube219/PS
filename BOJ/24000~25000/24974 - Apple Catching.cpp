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
    int n;
    cin >> n;
    struct Data
    {
        int x, y, num;
    };
    vector<Data> cow, apple;
    for(int i = 0; i < n; ++i) {
        int q, t, x, num;
        cin >> q >> t >> x >> num;
        if(q == 1) cow.push_back({ x + t, t - x, num });
        else apple.push_back({ x + t, t - x, num });
    }

    sort(cow.begin(), cow.end(), [](const Data& l, const Data& r) {
        return l.y > r.y;
    });
    sort(apple.begin(), apple.end(), [](const Data& l, const Data& r) {
        return l.y > r.y;
    });

    int res = 0;
    multimap<int, int> mp;
    while(apple.size() > 0) {
        auto [ax, ay, anum] = apple.back();
        apple.pop_back();

        while(cow.size() > 0 && ay >= cow.back().y) {
            mp.insert({ -cow.back().x, cow.back().num });
            cow.pop_back();
        }

        auto it = mp.lower_bound(-ax);
        while(anum > 0 && it != mp.end()) {
            int v = min(anum, it->second);
            anum -= v;
            it->second -= v;
            res += v;

            auto nxtIt = next(it);
            if(it->second == 0) mp.erase(it);

            it = nxtIt;
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
