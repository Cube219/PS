#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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

    vector<vector<int>> t;
    int stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    t.resize(stLeaf * 2);

    auto apply = [&](auto&& self, int cl, int cr, int l, int r, int node, int v) -> void {
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            t[node].push_back(v);
            return;
        }
        int m = (cl + cr) / 2;
        self(self, cl, m, l, r, node * 2, v);
        self(self, m + 1, cr, l, r, node * 2 + 1, v);
    };

    map<int, int> st;
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        if(v > 0) {
            st.insert({ v, i });
        } else {
            // range 적용
            auto it = st.find(-v);
            apply(apply, 0, stLeaf - 1, it->second, i - 1, 1, -v);
            st.erase(it);
        }
    }
    for(auto& it : st) {
        apply(apply, 0, stLeaf - 1, it.second, n - 1, 1, it.first);
    }

    auto add = [](vector<int>& basis, int v) {
        while(v > 0) {
            int msb = 0;
            for(int i = 31 - 1; i >= 0; --i) {
                if(v & (1LL << i)) {
                    msb = i;
                    break;
                }
            }
            if(basis[msb] == 0) {
                basis[msb] = v;
                return;
            }
            v ^= basis[msb];
        }
    };
    auto get = [](vector<int>& basis) {
        int res = 0;
        for(int i = 31 - 1; i >= 0; --i) {
            if(res < (res ^ basis[i])) res ^= basis[i];
        }
        return res;
    };

    auto dfs = [&](auto&& self, int cl, int cr, int node, vector<int>& parBasis) -> void {
        vector<int> basis = parBasis;
        for(int v : t[node]) {
            add(basis, v);
        }
        if(cl == cr) {
            if(cl < n) cout << get(basis) << "\n";
            return;
        }
        int m = (cl + cr) / 2;
        self(self, cl, m, node * 2, basis);
        self(self, m + 1, cr, node * 2 + 1, basis);
    };
    vector<int> rtBasis(31, 0);
    dfs(dfs, 0, stLeaf - 1, 1, rtBasis);
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
