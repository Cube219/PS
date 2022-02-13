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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    struct Trie
    {
        int nxt[2];
        ll cnt;
        Trie()
        {
            nxt[0] = nxt[1] = -1;
            cnt = 0;
        }
    };
    vector<Trie> t;
    t.emplace_back();
    auto insert = [&](int v) {
        int cur = 0;
        for(int i = 30 - 1; i >= 0; --i) {
            int bit = (v & (1 << i)) ? true : false;
            if(t[cur].nxt[bit] == -1) {
                t[cur].nxt[bit] = t.size();
                t.emplace_back();
            }
            cur = t[cur].nxt[bit];
        }
        t[cur].cnt++;
    };
    for(int v : a) insert(v);

    auto dfs = [&](auto&& self, int cur) -> ll {
        for(int i = 0; i < 2; ++i) {
            if(t[cur].nxt[i] != -1) {
                t[cur].cnt += self(self, t[cur].nxt[i]);
            }
        }
        return t[cur].cnt;
    };
    dfs(dfs, 0);

    auto getLess = [&](int v) {
        ll res = 0;
        int cur = 0;
        for(int i = 30 - 1; i >= 0; --i) {
            int mask = 1 << i;
            int vbit = v & mask ? 1 : 0;

            if(k & mask) {
                // 해당 bit 0으로 만드는 경우
                if(t[cur].nxt[vbit] != -1) {
                    int nxt = t[cur].nxt[vbit];
                    res += t[nxt].cnt;
                }
                if(t[cur].nxt[1 - vbit] == -1) break;
                cur = t[cur].nxt[1 - vbit];
            } else {
                if(t[cur].nxt[vbit] == -1) break;
                cur = t[cur].nxt[vbit];
            }

        }
        return res;
    };

    ll res = 0;
    for(int v : b) {
        res += getLess(v);
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
