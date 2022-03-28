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
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) {
        cin >> v;
        v--;
    }

    vector<char> has(n, false), visit(n, false);
    int cycleSt = -1;
    vector<int> st;
    auto dfs = [&](auto&& self, int cur) -> void {
        visit[cur] = true;

        int nxt = d[cur];
        if(visit[nxt] == false) {
            self(self, nxt);
        } else {
            cycleSt = nxt;
        }

        st.push_back(cur);
        if(cur == cycleSt) {
            cycleSt = -1;
            for(int pos : st) has[pos] = true;
            st.clear();
        }
    };

    for(int i = 0; i < n; ++i) {
        if(visit[i]) continue;

        st.clear();
        dfs(dfs, i);
    }

    int res = 0;
    for(int i = 0; i < n; ++i) {
        if(has[i] == false) res++;
    }
    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
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
