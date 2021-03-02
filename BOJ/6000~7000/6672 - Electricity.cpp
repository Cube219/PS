#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[10001];

int d[10001], dNum = 1;
vector<vector<pair<int, int>>> bcc;
vector<pair<int, int>> st;

int cnt[10001];
bool has[10001];
int gNum;

void init()
{
    for(int i = 0; i < n; ++i) {
        g[i].clear();
        d[i] = 0;
        cnt[i] = 0;
        has[i] = false;
    }
    dNum = 1;
    st.clear();
    bcc.clear();
    gNum = 0;
}

int dfs(int cur, int prev)
{
    d[cur] = dNum++;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(nxt == prev) continue;

        if(d[nxt] == 0 || d[cur] > d[nxt]) {
            st.push_back({ cur, nxt });
        }

        if(d[nxt] != 0) ret = min(ret, d[nxt]);
        else {
            int t = dfs(nxt, cur);
            if(t >= d[cur]) {
                bcc.push_back({});
                vector<pair<int, int>>& cbcc = bcc.back();
                while(1) {
                    auto top = st.back();
                    st.pop_back();

                    cbcc.push_back(top);
                    if(top.first == cur) break;
                }
            }
            ret = min(ret, t);
        }
    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        init();

        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        for(int i = 0; i < n; ++i) {
            if(d[i] == 0) {
                dfs(i, -1);
                gNum++;
            }
        }

        for(int i = 0; i < bcc.size(); ++i) {
            auto& cbcc = bcc[i];

            for(int j = 0; j < n; ++j) {
                has[j] = false;
            }
            for(int j = 0; j < cbcc.size(); ++j) {
                has[cbcc[j].first] = true;
                has[cbcc[j].second] = true;
            }
            for(int j = 0; j < n; ++j) {
                if(has[j] == true) cnt[j]++;
            }
        }

        int res = -1;
        for(int i = 0; i < n; ++i) {
            res = max(res, cnt[i]);
        }
        cout << res + gNum - 1 << "\n";
    }

    return 0;
}
