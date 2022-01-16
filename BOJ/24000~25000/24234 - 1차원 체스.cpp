#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Trie
{
    unordered_map<int, int> nxt;
    int cnt = 0;
};

void solve()
{
    vector<Trie> trie;
    trie.emplace_back();

    auto insert = [&](vector<int>& str) {
        int cur = 0;
        for(int ch : str) {
            if(trie[cur].nxt.find(ch) == trie[cur].nxt.end()) {
                trie[cur].nxt[ch] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].nxt[ch];
        }
        trie[cur].cnt++;
    };

    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        vector<int> d(num);
        for(auto& v : d) cin >> v;

        insert(d);
    }

    vector<ll> res(10001, 0);

    auto dfs = [&](auto&& self, int ch, int cur) -> ll {
        ll num = 0;
        for(auto [nch, nxt] : trie[cur].nxt) {
            ll ret = self(self, nch, nxt);
            if(ch != -1) res[ch] += num * ret;
            num += ret;
        }
        num += trie[cur].cnt;
        return num;
    };
    dfs(dfs, -1, 0);

    for(int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        cout << res[a] << "\n";
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
