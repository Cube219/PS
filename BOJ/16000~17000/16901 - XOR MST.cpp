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
    for(auto& v : d)
        cin >> v;

    sort(d.begin(), d.end());

    struct Trie
    {
        int nxt[2];
        Trie() { nxt[0] = nxt[1] = -1; }
    };
    vector<Trie> t;
    auto insert = [&](int v) {
        int cur = 0;
        for(int i = 30 - 1; i >= 0; --i) {
            int bit = (v & (1 << i)) ? 1 : 0;
            if(t[cur].nxt[bit] == -1) {
                t[cur].nxt[bit] = t.size();
                t.emplace_back();
            }
            cur = t[cur].nxt[bit];
        }
    };
    auto search = [&](int v) {
        int cur = 0;
        int res = 0;
        for(int i = 30 - 1; i >= 0; --i) {
            int bit = (v & (1 << i)) ? 1 : 0;
            if(t[cur].nxt[bit] == -1) {
                res |= 1 << i;
                cur = t[cur].nxt[1 - bit];
            } else {
                cur = t[cur].nxt[bit];
            }
        }

        return res;
    };
    auto getmin = [&](int l1, int r1, int l2, int r2) -> int {
        if(l1 > r1 || l2 > r2)
            return 0;
        t.clear();
        t.emplace_back();
        for(int i = l1; i <= r1; ++i) {
            insert(d[i]);
        }

        int res = INF;
        for(int i = l2; i <= r2; ++i) {
            res = min(res, search(d[i]));
        }
        return res;
    };

    auto p = [&](auto&& self, int l, int r, int bit) -> ll {
        if(bit == 0 || l >= r)
            return 0;

        int m = l;
        for(int i = l; i <= r; ++i) {
            if(d[i] & bit) {
                m = i;
                break;
            }
        }

        ll res = self(self, l, m - 1, bit >> 1) + self(self, m, r, bit >> 1);
        if(l <= m - 1 && m <= r) {
            res += getmin(l, m - 1, m, r);
        }

        return res;
    };
    cout << p(p, 0, n - 1, 1 << 30);
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
