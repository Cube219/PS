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
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    for(auto& v : d)
        cin >> v;

    vector<int> sum(n + 1);
    sum[0] = 0;
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] ^ d[i];
    }

    struct Trie
    {
        int nxt[2];
        int cnt;
        Trie() {
            nxt[0] = nxt[1] = -1;
            cnt = 0;
        }
    };
    vector<Trie> t;
    t.emplace_back();
    auto insert = [&](int v) {
        int cur = 0;
        vector<int> st;
        st.push_back(0);
        for(int i = 20 - 1; i >= 0; --i) {
            int bit = (v & (1 << i)) ? 1 : 0;
            if(t[cur].nxt[bit] == -1) {
                t[cur].nxt[bit] = t.size();
                t.emplace_back();
            }
            cur = t[cur].nxt[bit];
            st.push_back(cur);
        }
        for(auto idx : st) {
            t[idx].cnt++;
        }
    };
    auto search = [&](int v) {
        ll res = 0;
        int cur = 0;
        for(int i = 20 - 1; i >= 0; --i) {
            int bit = (v & (1 << i)) ? 1 : 0;
            int kbit = (k & (1 << i)) ? 1 : 0;
            if(kbit == 0) {
                if(bit == 0) {
                    if(t[cur].nxt[0] == -1)
                        break;
                    cur = t[cur].nxt[0];
                } else {
                    if(t[cur].nxt[1] == -1)
                        break;
                    cur = t[cur].nxt[1];
                }
            } else {
                if(bit == 0) {
                    if(t[cur].nxt[0] != -1) {
                        res += t[t[cur].nxt[0]].cnt;
                    }
                    if(t[cur].nxt[1] == -1)
                        break;
                    cur = t[cur].nxt[1];
                } else {
                    if(t[cur].nxt[1] != -1) {
                        res += t[t[cur].nxt[1]].cnt;
                    }
                    if(t[cur].nxt[0] == -1)
                        break;
                    cur = t[cur].nxt[0];
                }
            }
        }

        return res;
    };

    ll res = 0;
    insert(0);
    for(int i = 0; i < n; ++i) {
        res += search(sum[i + 1]);
        insert(sum[i + 1]);
    }
    cout << res;
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
