#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
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
    struct Edge
    {
        int nxt;
        ll v;
    };
    vector<vector<Edge>> g(100);
    vector<int> in(100, 0), out(100, 0);
    ll mnV = 99909121313;
    int mnIdx = 0;
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int l = (s[0] - '0') * 10 + (s[1] - '0');
        int r = (s[8] - '0') * 10 + (s[9] - '0');
        ll v = 0;
        for(char ch : s) {
            v *= 10;
            v += ch - '0';
        }
        g[l].push_back({ r, v });
        out[l]++;
        in[r]++;

        if(mnV > v) {
            mnV = v;
            mnIdx = l;
        }
    }

    bool pos = true;
    int stIdx = -1, edIdx = -1;
    for(int i = 0; i < 100; ++i) {
        if(in[i] == out[i]) continue;
        if(in[i] + 1 == out[i]) {
            if(stIdx != -1) {
                pos = false;
            } else {
                stIdx = i;
            }
        } else if(in[i] == out[i] + 1) {
            if(edIdx != -1) {
                pos = false;
            } else {
                edIdx = i;
            }
        } else pos = false;
    }
    if(pos == false) {
        cout << "impossible";
        return;
    }
    if(stIdx == -1 && edIdx == -1) stIdx = mnIdx;
    else if(stIdx == -1 || edIdx == -1) {
        cout << "impossible";
        return;
    }

    for(auto& v : g) {
        sort(v.begin(), v.end(), [](const Edge& l, const Edge& r) {
            return l.v > r.v;
        });
    }

    vector<ll> res;
    auto dfs = [&](auto&& self, int cur, ll lastEg) -> void {
        while(g[cur].size() > 0) {
            auto [nxt, v] = g[cur].back();
            g[cur].pop_back();

            self(self, nxt, v);
        }
        res.push_back(lastEg);
    };
    dfs(dfs, stIdx, -1);
    if(res.size() != n + 1) {
        cout << "impossible";
        return;
    }

    for(int i = (int)res.size() - 2; i >= 0; --i) {
        cout << setfill('0') << setw(10) << res[i] << "\n";
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
