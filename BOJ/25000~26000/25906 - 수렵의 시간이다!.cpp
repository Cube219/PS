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
    int t, k;
    cin >> t >> k;
    vector<vector<int>> attack(5);
    for(auto& a : attack) {
        int num;
        cin >> num;
        a.resize(num + 1);
        a[0] = 0;
        for(int i = 1; i <= num; ++i) {
            cin >> a[i];
        }
    }

    struct Equip
    {
        int c;
        vector<int> v;
    };
    vector<vector<Equip>> eqList(3);
    for(auto& eqL : eqList) {
        int m;
        cin >> m;
        eqL.resize(m);
        for(auto& eq : eqL) cin >> eq.c;
        for(auto& eq : eqL) {
            eq.v.resize(5);
            for(auto& v : eq.v) cin >> v;
        }
    }

    int res = 0;
    vector<int> level(5, 0);

    auto applyReinforcement = [&](int curAttack, int remainGold) {
        if(remainGold < k) return;

        for(int i = 0; i < 5; ++i) {
            if(level[i] == 0) continue;
            int v = curAttack;
            if(level[i] < (int)attack[i].size()) {
                v -= attack[i][level[i]] - attack[i][level[i] - 1];
            }
            for(int j = 0; j < 5; ++j) {
                if(i == j || level[j] + 1 >= (int)attack[j].size()) continue;
                
                v -= attack[j][level[j]] - attack[j][level[j] + 1];
                res = max(res, v);
                v += attack[j][level[j]] - attack[j][level[j] + 1];
            }
        }
    };

    auto bt = [&](auto&& self, int idx, int remainGold) -> void {
        if(idx == 3) {
            int curAttack = 0;
            for(int i = 0; i < 5; ++i) {
                curAttack += attack[i][min((int)attack[i].size() - 1, level[i])];
            }
            res = max(res, curAttack);
            applyReinforcement(curAttack, remainGold);
            return;
        }
        // Not equip
        self(self, idx + 1, remainGold);
        // equip
        for(auto& eq : eqList[idx]) {
            if(remainGold < eq.c) continue;

            for(int i = 0; i < 5; ++i) {
                level[i] += eq.v[i];
            }
            self(self, idx + 1, remainGold - eq.c);
            for(int i = 0; i < 5; ++i) {
                level[i] -= eq.v[i];
            }
        }
    };
    bt(bt, 0, t);

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
