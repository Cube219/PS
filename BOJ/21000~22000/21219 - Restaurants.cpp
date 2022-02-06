#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> c(m);
    for(auto& v : c) cin >> v;
    vector<vector<int>> preC(n), preR(m);
    auto get_ints = [&]() {
        string buf;
        getline(cin, buf);
        vector<int> res;
        int cur = 0;
        for(char ch : buf) {
            if(ch == ' ') {
                res.push_back(cur);
                cur = 0;
            } else {
                cur *= 10;
                cur += ch - '0';
            }
        }
        res.push_back(cur);
        if(res[0] == 0) res.clear();

        return res;
    };
    get_ints();
    for(int i = 0; i < n; ++i) {
        preC[i] = get_ints();
        for(auto& v : preC[i]) v--;
    }
    for(int i = 0; i < m; ++i) {
        preR[i] = get_ints();
        for(auto& v : preR[i]) v--;
    }
    vector<map<int, int>> pri(m);
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < preR[i].size(); ++j) {
            pri[i].insert({ preR[i][j], j });
        }
    }

    vector<priority_queue<pair<int, int>>> d(m);
    vector<bool> isMatch(n, false);
    queue<int> q;
    for(int i = 0; i < n; ++i) q.push(i);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        if(isMatch[cur] == true) continue;

        for(int r : preC[cur]) {
            auto it = pri[r].find(cur);
            if(it == pri[r].end()) continue;

            int myPri = it->second;
            if(d[r].size() == c[r]) {
                auto [oldPri, oldc] = d[r].top();
                if(oldPri > myPri) {
                    d[r].pop();
                    isMatch[oldc] = false;
                    q.push(oldc);
                } else {
                    continue;
                }
            }

            d[r].push({myPri, cur});
            isMatch[cur] = true;
            break;
        }
    }

    for(int i = 0; i < n; ++i) {
        if(isMatch[i] == true) cout << i + 1 << "\n";
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
