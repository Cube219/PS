#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    int msbk = 0;
    for(int i = 31 - 1; i >= 0; --i) {
        if(k & (1 << i)) {
            msbk = i;
            break;
        }
    }

    vector<int> d(n);
    unordered_map<int, vector<pair<int, int>>> mp;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        d[i] = a;
        int left = a >> (msbk + 1);
        int right = a & ((1 << (msbk + 1)) - 1);
        mp[left].push_back({ right, i });
    }

    struct Trie
    {
        int nxt[2];
        int id;
        Trie()
        {
            nxt[0] = -1;
            nxt[1] = -1;
            id = -1;
        }
    };
    vector<Trie> trie;
    auto add = [&](int v, int id) {
        int cur = 0;
        for(int i = 31 - 1; i >= 0; --i) {
            int bit = v & (1 << i);
            bit = bit > 0 ? 1 : 0;

            if(trie[cur].nxt[bit] == -1) {
                trie[cur].nxt[bit] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].nxt[bit];
        }
        trie[cur].id = id;
    };

    vector<int> res;
    for(auto& [left, rlist] : mp) {
        trie.clear();
        trie.emplace_back();
        int mxv = -1, id1 = 0, id2 = 0;
        for(auto [r, id] : rlist) {
            add(r, id);

            int cur = 0, mx = 0;
            for(int i = 31 - 1; i >= 0; --i) {
                int bit = r & (1 << i);
                bit = bit > 0 ? 1 : 0;
                if(trie[cur].nxt[1 - bit] != -1) {
                    mx |= (1 << i);
                    cur = trie[cur].nxt[1 - bit];
                } else {
                    cur = trie[cur].nxt[bit];
                }
            }
            if(mxv < mx) {
                mxv = mx;
                id1 = id;
                id2 = trie[cur].id;
            }
        }

        res.push_back(id1);
        if((d[id1] ^ d[id2]) >= k) res.push_back(id2);
    }

    if(k == 0) {
        res.resize(n);
        iota(res.begin(), res.end(), 0);
    }

    if(res.size() <= 1) cout << "-1\n";
    else {
        cout << res.size() << "\n";
        for(int v : res) cout << v + 1 << " ";
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
