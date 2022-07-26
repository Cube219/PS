#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    map<int, int> lList, rList;
    set<pair<int, int>> rng;
    for(int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;

        auto it = lList.find(l);
        if(it == lList.end()) it = lList.insert({ l, 0 }).first;
        it->second = max(it->second, r);

        it = rList.find(r);
        if(it == rList.end()) it = rList.insert({ r, INF }).first;
        it->second = min(it->second, l);

        rng.insert({ l, r });
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;

        if(rng.find({ l, r }) != rng.end()) {
            cout << "1\n";
            continue;
        }

        auto it = lList.find(l);
        if(it != lList.end() && r <= it->second) {
            it = rList.find(r);
            if(it != rList.end() && it->second <= l) {
                cout << "2\n";
                continue;
            }
        }
        cout << "-1\n";
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
