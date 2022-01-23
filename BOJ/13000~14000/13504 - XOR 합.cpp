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
    vector<ll> d(n);
    for(auto& v : d)
        cin >> v;

    vector<ll> sum(n + 1);
    sum[0] = 0;
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] ^ d[i];
    }

    struct Trie
    {
        int nxt[2];
        Trie() { nxt[0] = nxt[1] = -1; }
    };
    vector<Trie> trie;
    trie.emplace_back();
    auto insert = [&](ll v) {
        int cur = 0;
        for(int i = 32 - 1; i >= 0; i--) {
            int bit = (v & (1LL << i)) ? 1 : 0;
            if(trie[cur].nxt[bit] == -1) {
                trie[cur].nxt[bit] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].nxt[bit];
        }
    };
    auto search = [&](ll v) {
        ll res = 0;
        int cur = 0;
        for(int i = 32 - 1; i >= 0; --i) {
            int bit = (v & (1LL << i)) ? 1 : 0;
            if(trie[cur].nxt[1 - bit] != -1) {
                cur = trie[cur].nxt[1 - bit];
                res |= (1LL << i);
            } else {
                cur = trie[cur].nxt[bit];
            }
        }

        return res;
    };

    ll res = 0;
    for(ll v : sum) {
        insert(v);
        res = max(res, search(v));
    }

    cout << res << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
