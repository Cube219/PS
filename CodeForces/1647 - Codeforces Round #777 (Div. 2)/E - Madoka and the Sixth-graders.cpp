#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> p(n), a(n);
    for(auto& v : p) {
        cin >> v;
        v--;
    }
    for(auto& v : a) cin >> v;

    vector<int> inNum(n, 0);
    for(int i = 0; i < n; ++i) {
        inNum[p[i]]++;
    }
    int notUseNum = 0, idx = -1;
    for(int i = 0; i < n; ++i) {
        if(inNum[i] > 0) continue;
        notUseNum++;
        if(idx == -1) idx = i;
    }

    int step = (a[idx] - n - 1) / notUseNum;
    if(step < 0) {
        for(int i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << "\n";
        return;
    }
    step++;

    vector<vector<int>> tb(n, vector<int>(30));
    for(int i = 0; i < n; ++i) {
        tb[i][0] = p[i];
    }
    for(int j = 1; j < 30; ++j) {
        for(int i = 0; i < n; ++i) {
            int nxt = tb[i][j - 1];
            tb[i][j] = tb[nxt][j - 1];
        }
    }

    vector<int> res(n, -1);
    set<int> remain;
    for(int i = 0; i < n; ++i) {
        remain.insert(i + 1);
    }
    for(int i = 0; i < n; ++i) {
        int cur = i;
        for(int j = 0; j < 30; ++j) {
            if(step & (1 << j)) {
                cur = tb[cur][j];
            }
        }

        auto it = remain.find(a[cur]);
        if(it != remain.end()) {
            res[i] = a[cur];
            remain.erase(it);
        } else {
            res[i] = -a[cur];
        }
    }

    for(int i = 0; i < n; ++i) {
        if(res[i] < 0) {
            auto it = remain.lower_bound(-res[i]);
            res[i] = *it;
            remain.erase(it);
        }
    }

    for(int v : res) cout << v << " ";
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
